//
// ORB.h
//
// $Id: //poco/1.7/RemotingNG/include/Poco/RemotingNG/ORB.h#3 $
//
// Library: RemotingNG
// Package: ORB
// Module:  ORB
//
// Definition of the ORB class.
//
// Copyright (c) 2006-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef RemotingNG_ORB_INCLUDED
#define RemotingNG_ORB_INCLUDED


#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/Skeleton.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"
#include "Poco/RemotingNG/ProxyFactoryManager.h"
#include "Poco/RemotingNG/ProxyFactory.h"
#include "Poco/RemotingNG/Listener.h"
#include "Poco/RefCountedObject.h"
#include "Poco/BasicEvent.h"
#include "Poco/AutoPtr.h"
#include "Poco/Logger.h"
#include "Poco/Mutex.h"
#include "Poco/SingletonHolder.h"
#include <map>
#include <set>
#include <vector>


namespace Poco {
namespace RemotingNG {


class ServerTransport;


class RemotingNG_API ORB
	/// The Object Request Broker, or ORB, is the central object in the Remoting machinery.
	/// The ORB is a singleton which manages Listener, RemoteObject and Skeleton instances on 
	/// the server side, as well as Proxy creation on the client side.
	///
	/// A client can use findObject() to obtain an interface for accessing a service object.
	/// Depending on whether the service object has been registered on the same ORB, or not,
	/// the ORB will either return a RemoteObject (with forwards calls locally, without the
	/// need for serialization/deserialization), or a Proxy.
	/// 
	/// It is recommended to use the various helper classes
	/// (client helper, server helper) generated by the Remoting code 
	/// generator to obtain an instance of an object instead of using
	/// findObject() directly.
{
public:
	typedef std::vector<Listener::Ptr> ListenerVec;
	
	struct ObjectRegistration
		/// Event argument for objectRegistered and objectUnregistered events.
	{
		std::string uri;
		std::string alias;
		RemoteObject::Ptr pRemoteObject;
		Listener::Ptr pListener;
	};
	
	Poco::BasicEvent<const ObjectRegistration> objectRegistered;
		/// Fired when an object has been registered 
		/// by calling registerObject().
		
	Poco::BasicEvent<const ObjectRegistration> objectUnregistered;
		/// Fired when an object has been unregistered
		/// by calling unregisterObject().

	static ORB& instance();
		/// Returns a reference to the global ORB.

	void shutdown();
		/// Stops all Listener instances and removes them, as well as
		/// all RemoteObject and Skeleton instances from the ORB.

	bool invoke(const Listener& listener, const std::string& uri, ServerTransport& transport) const;
		/// Invoke a method on the object registered for the given Listener and URI.
		///
		/// The ORB will look up the Skeleton registered for the object, and perform
		/// the actual invocation through the Skeleton.
		///
		/// Returns true if the object with the given URI was found, false otherwise.
		///
		/// URI can be a complete URI, or a URI path. In any case, only the URI path will
		/// be considered. The given URI can be an alias URI, which will be matched against
		/// registered aliases.

	bool invoke(const std::string& objectPath, ServerTransport& transport) const;
		/// Invoke a method on the object registered for the given object path.
		///
		/// The ORB will look up the Skeleton registered for the object, and perform
		/// the actual invocation through the Skeleton.
		///
		/// Returns true if the object with the given URI was found, false otherwise.
		///
		/// The format of objectPath is <protocol>/<endpoint>/<typeId>/<objectId>.
		
	Identifiable::Ptr findObject(const std::string& uri) const;
		/// Return an interface for the service object identified by the given URI.
		///
		/// Depending on whether the service object has been registered on the same ORB, or not,
		/// the ORB will either return a RemoteObject (with forwards calls locally, without the
		/// need for serialization/deserialization), or a Proxy.
		///
		/// The URI must have the following format: <scheme>://<authority>/<protocol>/<typeId>/<objectId>
		///
		/// This method is usually not called directly, but indirectly through the generated
		/// client helper class instead. The client helper class performs an appropriate cast
		/// to the actual interface class.
		///
		/// The strategy for determining whether the URI references a local object is as follows:
		/// First, check whether the URI matches one of the URIs registered with the local ORB.
		/// If so, return the matching RemoteObject instance.
		/// If no matching URI is found, ask all registered Listener instances whether they "know"
		/// the given URI. To do this, first the protocol, TypeId and ObjectId are extracted
		/// from the URI. Then, each Listener handling the protocol is asked to create an URI
		/// for TypeId and ObjectId. If this URI matches one of the registered URIs, check
		/// whether the respective Listener actually handles the endpoint contained in the URI
		/// (by calling Listener::handlesURI()).
		/// If so, return the RemoteObject. Otherwise, return a new Proxy object.

	Identifiable::Ptr findObject(const std::string& uri, const Identifiable::TypeId& tid, const std::string& transport) const;
		/// Return an interface for the service object identified by the given URI, TypeID and transport name.
		/// This is useful for Transport implementations that allow the use of URIs that do
		/// not conform to the standard Remoting URI format.
		///
		/// Depending on whether the service object has been registered on the same ORB, or not,
		/// the ORB will either return a RemoteObject (with forwards calls locally, without the
		/// need for serialization/deserialization), or a Proxy.
		///
		/// This method is usually not called directly, but indirectly through the generated
		/// client helper class instead. The client helper class performs an appropriate cast
		/// to the actual interface class.
		///
		/// If the given URI exactly matches one of the URIs registered with the ORB, the corresponding
		/// RemoteObject instance is returned. Otherwise a new Proxy instance is created and returned.

	std::string registerListener(Listener::Ptr pListener);
		/// Registers the Listener at the ORB. The local endpoint of the Listener
		/// must be unique. Registration will fail with an exception if it is not.
		///
		/// Returns a string uniquely identifying the Listener, which can be used for
		/// registering service objects (see registerObject()).

	void unregisterListener(const std::string& listenerId, bool autoRemoveObjects = false);
		/// Unregisters a Listener, identified by its ID. 
		///
		/// Will automatically remove all service objects associated with that listener
		/// if autoRemoveObjects is set to true, otherwise it will check if objects are still registered
		/// and will fail with a RemotingException.

	ListenerVec listeners() const;
		/// Returns a vector containing all registered Listener objects.
		
	std::vector<std::string> listenerIds() const;
		/// Returns a vector containing the IDs of all registered Listener objects.

	std::vector<std::string> listenerIds(const std::string& protocol) const;
		/// Returns a vector containing the IDs of all registered Listener objects
		/// supporting the given protocol.
		
	Listener::Ptr findListener(const std::string& listenerId) const;
		/// Returns the Listener object with the given ID, or a null pointer
		/// if no Listener with this ID exists.

	void registerSkeleton(const Identifiable::TypeId& tid, Skeleton::Ptr pSkeleton);
		/// Registers a Skeleton for the given class identified by TypeID.
		///
		/// Duplicate registration of a class is ignored.

	void unregisterSkeleton(const Identifiable::TypeId& tid, bool autoRemoveObjects = false);
		/// Unregisters the Skeleton for the given type, if found.
		///
		/// If objects are still registered and autoRemoveObjects is false, it will fail with a RemotingException.

	Skeleton::Ptr skeletonForClass(const Identifiable::TypeId& tid) const;
		/// Returns a Skeleton for the given type.
		///
		/// Throws an exception if no Skeleton exists for the given TypeId.

	void registerProxyFactory(const Identifiable::TypeId& tid, ProxyFactory::Ptr pProxyFactory);
		/// Registers a ProxyFactory for the given class identified by TypeID.
		///
		/// Duplicate registration of a class is ignored.

	void unregisterProxyFactory(const Identifiable::TypeId& tid);
		/// Unregisters a proxy factory for the given type, if found.

	void registerClass(const Identifiable::TypeId& tid, ProxyFactory::Ptr pProxyFactory, Skeleton::Ptr pSkeleton);
		/// Registers a ProxyFactory for the given class identified by TypeID and Skeleton.
		///
		/// Duplicate registration of a class is ignored.

	void unregisterClass(const Identifiable::TypeId& tid, bool autoRemoveObjects = false);
		/// Unregisters ProxyFactory, Skeleton and RemoteObject for the given class identified by TypeID.
		///
		/// If objects are still registered and autoRemoveObjects is false, it will fail with a RemotingException.

	std::string registerObject(RemoteObject::Ptr pRemoteObject, const std::string& listenerId);
		/// Registers a RemoteObject with the ORB and the Listener instance
		/// uniquely identified by the Listener ID.
		///
		/// A class (TypeId) must have already been registered for the object.
		///
		/// Duplicate registration of an object results in an exception.
		///
		/// If the registration fails due to the ORB being in shutdown mode, an exception is thrown.
		///
		/// If an URI has been assigned to the RemoteObject (by calling remoting__setURI()), that
		/// URI's path is registered as an alias for the object.
		///
		/// Returns the URI created for the object.

	void unregisterObject(const std::string& uri);
		/// Unregisters a service object identified by URI from the ORB, if found. 
		///
		/// Skeleton and Transport must still exist.
		
	void registerEventDispatcher(const std::string& uri, EventDispatcher::Ptr pDispatcher);
		/// Registers an EventDispatcher for the RemoteObject with the given URI.
		///
		/// Multiple EventDispatcher objects can be registered for the same RemoteObject,
		/// as long as each EventDispatcher uses a different protocol.
		
	void unregisterEventDispatcher(const std::string& uri, const std::string& protocol);
		/// Unregisters the EventDispatcher handling the given protocol from
		/// the RemoteObject with the given URI.
		
	void unregisterEventDispatchers(const std::string& uri);
		/// Unregisters all EventDispatcher objects registered for
		/// the RemoteObject with the given URI.
		
	EventDispatcher::Ptr findEventDispatcher(const std::string& uri, const std::string& protocol) const;
		/// Return the EventDispatcher handling the given protocol, for the RemoteObject
		/// identified by URI. The given URI can be a fully-qualified URI (the result
		/// of registerObject()), or an object path. The format of an object path is 
		/// <protocol>/<endpoint>/<typeId>/<objectId>. If an object path is specified, protocol
		/// can be empty.
		///
		/// Throws a Poco::NotFoundException if no matching EventDispatcher has been registered.

private:
	typedef std::map<std::string, EventDispatcher::Ptr> EventDispatchers;
	
	struct RemoteObjectInfo: public Poco::RefCountedObject
	{
		typedef Poco::AutoPtr<RemoteObjectInfo> Ptr;

		RemoteObject::Ptr pRemoteObject;
		Skeleton::Ptr pSkeleton;
		Listener::Ptr pListener;
		std::string objectPath;
		std::string uri;
		EventDispatchers eventDispatchers;
	};
	typedef std::map<std::string, Listener::Ptr> ListenerMap;
	typedef std::map<std::string, RemoteObjectInfo::Ptr> RemoteObjects;
	typedef std::map<Identifiable::TypeId, Skeleton::Ptr> Skeletons;
	typedef std::map<std::string, std::string> URIAliases;
	typedef std::set<std::string> LocalURIs;

	ORB();
	~ORB();
	ORB(const ORB&);
	ORB& operator = (const ORB&);

	RemoteObjectInfo::Ptr findLocalObject(const Identifiable::TypeId& tid, const Identifiable::ObjectId& oid, const std::string& protocol) const;
	URIAliases::const_iterator findAlias(const std::string& path) const;

	bool                _enabled;
	ListenerMap         _listeners;         /// Maps endpoints to Listener objects
	ProxyFactoryManager _proxyFactories;
	RemoteObjects       _remoteObjects;     /// Maps object paths to RemoteObjectInfo objects
	RemoteObjects       _remoteObjectURIs;  /// Maps URIs to RemoteObjectInfo objects
	Skeletons           _skeletons;         /// Maps TypeIds to Skeleton objects
	URIAliases          _uriAliases;
	Poco::Logger&       _logger;
    mutable Poco::FastMutex _mutex;
	
	friend class Poco::SingletonHolder<ORB>;
};


} } // namespace Poco::RemotingNG


#endif // RemotingNG_ORB_INCLUDED
