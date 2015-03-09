/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2013 Magister Solutions Ltd
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Sami Rantanen <sami.rantanen@magister.fi>
 */
#ifndef __SATELLITE_HELPER_H__
#define __SATELLITE_HELPER_H__

#include <string>

#include "ns3/object.h"
#include "ns3/trace-helper.h"
#include "ns3/output-stream-wrapper.h"
#include "ns3/node-container.h"
#include "ns3/ipv4-address-helper.h"
#include "ns3/csma-helper.h"
#include "ns3/satellite-antenna-gain-pattern-container.h"
#include "satellite-user-helper.h"
#include "satellite-beam-helper.h"
#include "satellite-beam-user-info.h"
#include "satellite-conf.h"
#include "ns3/satellite-position-allocator.h"
#include "ns3/satellite-rx-power-input-trace-container.h"
#include "ns3/satellite-rx-power-output-trace-container.h"
#include "ns3/satellite-interference-input-trace-container.h"
#include "ns3/satellite-interference-output-trace-container.h"
#include "ns3/satellite-fading-output-trace-container.h"
#include "ns3/satellite-fading-input-trace-container.h"

namespace ns3 {

/**
 * \brief Build a satellite network set with needed objects and configuration.
 *        Utilizes SatUserHelper and SatBeamHelper helper objects.
 */
class SatHelper : public Object
{
public:
  /**
   * definition for beam map key is beam ID and value is UT/user info.
   */
  typedef std::map<uint32_t, SatBeamUserInfo > BeamUserInfoMap_t;

  /**
   * \enum values for pre-defined scenarios to be used by helper when building
             satellite network topology base.
   *
   *  - NONE:         Not used.
   *  - SIMPLE:       Simple scenario used as base.
   *  - LARGER:       Larger scenario used as base.
   *  - FULL:         Full scenario used as base.
   */
  typedef enum
  {
    NONE,
    SIMPLE,
    LARGER,
    FULL
  } PreDefinedScenario_t;

  static TypeId GetTypeId (void);
  TypeId GetInstanceTypeId (void) const;

  /**
   * \brief Default constructor
   */
  SatHelper ();

  /**
   * \brief Create a base SatHelper for creating customized Satellite topologies.
   */
  SatHelper (std::string scenarioName);

  /**
   * Destructor for SatHelper
   */
  virtual ~SatHelper ()
  {
  }

  /**
   * \brief Create a pre-defined SatHelper to make life easier when creating Satellite topologies.
   */
  void CreatePredefinedScenario (PreDefinedScenario_t scenario);

  /**
   * Creates satellite objects according to user defined scenario.
   *
   * \param info information of the beams, and beam UTs and users in beams
   */
  void CreateUserDefinedScenario (BeamUserInfoMap_t& info);

  /**
   * Creates satellite objects according to user defined scenario.
   * Positions are read from different input files from file set by attribute ns3::SatConf::UtPositionInputFileName.
   *
   * \param info information of the beams, and beam UTs and users in beams
   * \param checkBeam Check that positions (set through SatConf) match with given beam
   * (the beam is the best according to configured antenna patterns).
   */
  void CreateUserDefinedScenarioFromListPositions (BeamUserInfoMap_t& info, bool checkBeam);

  /**
   * \param  node pointer to user node.
   *
   * \return address of the user.
   */
  Ipv4Address GetUserAddress (Ptr<Node> node);

  /**
   * \return container having UT users
   */
  NodeContainer GetUtUsers () const;

  /**
   * \return container having GW users.
   */
  NodeContainer GetGwUsers () const;

  /**
   * \return pointer to beam helper.
   */
  Ptr<SatBeamHelper> GetBeamHelper () const;

  /**
   * \return pointer to user helper.
   */
  Ptr<SatUserHelper> GetUserHelper () const;

  /**
   * Set multicast group to satellite network and IP router. Add needed routes to net devices.
   *
   * \param source Source node of the multicast group (GW or UT connected user node)
   * \param receivers Receiver nodes of the multicast group. (GW or UT connected user nodes)
   * \param sourceAddress Source address of the multicast group.
   * \param address Address of the multicast group.
   */
  void SetMulticastGroupRoutes (Ptr<Node> source, NodeContainer receivers, Ipv4Address sourceAddress, Ipv4Address groupAddress );

  inline NodeContainer GwNodes ()
  {
    return m_beamHelper->GetGwNodes ();
  }
  inline NodeContainer UtNodes ()
  {
    return m_beamHelper->GetUtNodes ();
  }
  inline Ptr<Node> GeoSatNode ()
  {
    return m_beamHelper->GetGeoSatNode ();
  }

  void DoDispose ();

private:
  typedef SatBeamHelper::MulticastBeamInfoItem_t  MulticastBeamInfoItem_t;
  typedef SatBeamHelper::MulticastBeamInfo_t      MulticastBeamInfo_t;

  /**
   * User helper
   */
  Ptr<SatUserHelper> m_userHelper;

  /**
   * Beam helper
   */
  Ptr<SatBeamHelper> m_beamHelper;

  /**
   * Gateway container
   */
  NodeContainer m_gwUser;

  /**
   * Configuration for satellite network.
   */
  Ptr<SatConf> m_satConf;

  /**
   * Trace callback for creation traces (details)
   */
  TracedCallback<std::string> m_creationDetailsTrace;

  /**
   * Trace callback for creation traces (summary)
   */

  TracedCallback<std::string> m_creationSummaryTrace;

  /**
   * Stream wrapper used for creation traces
   */
  Ptr<OutputStreamWrapper> m_creationTraceStream;

  /**
   * Stream wrapper used for UT position traces
   */
  Ptr<OutputStreamWrapper> m_utTraceStream;

  bool m_hasBeamNetworkSet;  ///< #m_beamNetworkAddress has been set a value.
  bool m_hasGwNetworkSet;    ///< #m_gwNetworkAddress has been set a value.
  bool m_hasUtNetworkSet;    ///< #m_utNetworkAddress has been set a value.

  Ipv4Address m_beamNetworkAddress;  ///< Initial network number of satellite devices, e.g., 10.1.1.0.
  Ipv4Address m_gwNetworkAddress;    ///< Initial network number of GW, router, and GW users, e.g., 10.2.1.0.
  Ipv4Address m_utNetworkAddress;    ///< Initial network number of UT and UT users, e.g., 10.3.1.0.

  /**
   * flag to check if scenario is already created.
   */
  bool m_scenarioCreated;

  /**
   * flag to indicate if creation trace should be enabled for scenario creation.
   */
  bool m_creationTraces;

  /**
   * flag to indicate if detailed creation trace should be enabled for scenario creation.
   */
  bool m_detailedCreationTraces;

  /**
   * flag to indicate if packet trace should be enabled after scenario creation.
   */
  bool m_packetTraces;

  /**
   * Number of UTs created per Beam in full or user-defined scenario
   */
  uint32_t m_utsInBeam;

  /**
   * Number of users created in public network (behind GWs) in full or user-defined scenario
   */
  uint32_t m_gwUsers;

  /**
   * Number of users created in end user network (behind every UT) in full or user-defined scenario
   */
  uint32_t m_utUsers;

  /**
   * Info for beam creation in user defined scenario.
   * first is ID of the beam and second is number of beam created in beam.
   * If second is zero then default number of UTs is created (number set by attribute UtCount)
   *
   * Info is set by attribute BeamInfo
   */
  BeamUserInfoMap_t m_beamUserInfos;

  /**
   * File name for scenario creation trace output
   */
  std::string m_scenarioCreationFileName;

  /**
   * File name for UT creation trace output
   */
  std::string m_utCreationFileName;

  /**
   * Antenna gain patterns for all spot-beams. Used for beam selection.
   */
  Ptr<SatAntennaGainPatternContainer> m_antennaGainPatterns;

  /**
   * User defined UT positions from SatConf.
   */
  Ptr<SatListPositionAllocator> m_utPositions;

  /**
   * Enables creation traces to be written in given file
   */
  void EnableCreationTraces ();

  /**
   * Enables creation traces in sub-helpers.
   */
  void EnableDetailedCreationTraces ();

  /**
   * Enable packet traces
   */
  void EnablePacketTrace ();

  /**
   * Sink for creation details traces
   * \param stream stream for traces
   * \param context context for traces
   * \param info creation info
   */
  static void CreationDetailsSink (Ptr<OutputStreamWrapper> stream, std::string context, std::string info);
  /**
   * Sink for creation summary traces
   * \param title creation summary title
   */
  void CreationSummarySink (std::string title);
  /**
   * Creates satellite objects according to simple scenario.
   */
  void CreateSimpleScenario ();
  /**
   * Creates satellite objects according to larger scenario.
   */
  void CreateLargerScenario ();
  /**
   * Creates satellite objects according to full scenario.
   */
  void CreateFullScenario ();

  /**
   * Creates satellite objects according to given beam info.
   * \param beamInfos information of the beam to create (and beams which are given in map)
   * \param gwUsers number of the users in GW(s) side
   */
  void DoCreateScenario (BeamUserInfoMap_t beamInfos, uint32_t gwUsers);

  /**
   * Creates trace summary starting with give title.
   * \param title title for summary
   * \returns std::string as summary
   */
  std::string CreateCreationSummary (std::string title);

  /**
   * Sets mobilities to created GW nodes.
   *
   * \param gws node container of UTs to set mobility
   */
  void SetGwMobility (NodeContainer gws);

  /**
   * Sets mobility to created Sat Geo node.
   *
   * \param node node pointer of Geo Satellite to set mobility
   */
  void SetGeoSatMobility (Ptr<Node> node);

  /**
   * Sets mobility to created UT nodes.
   *
   * \param uts node container of UTs to set mobility
   * \param beamId the spot-beam id, where the UTs should be placed
   *
   */
  void SetUtMobility (NodeContainer uts, uint32_t beamId);

  /**
   * Install Satellite Mobility Observer to nodes, if observer doesn't exist already in a node
   *
   * \param nodes Nodecontainer of nodes to install mobility observer.
   */
  void InstallMobilityObserver (NodeContainer nodes) const;

  /**
   * \brief Set the initial network number to use during allocation of satellite
   *        devices.
   * \param addr the initial network number, e.g., 10.1.1.0 (must be different
   *             from network numbers of GW and UT networks)
   * \return true if the operation is successful
   *
   * 255.255.255.0 will be used as the network mask.
   */
  bool SetBeamNetworkAddress (Ipv4Address addr);

  /// \return the initial network number of satellite devices
  Ipv4Address GetBeamNetworkAddress () const;

  /**
   * \brief Set the initial network number to use during allocation of GW,
   *        router, and GW users.
   * \param addr the initial network number, e.g., 10.2.1.0 (must be different
   *             from network numbers of beam and UT networks)
   * \return true if the operation is successful
   *
   * 255.255.255.0 will be used as the network mask.
   */
  bool SetGwNetworkAddress (Ipv4Address addr);

  /// \return the initial network number of GW, router, and GW users
  Ipv4Address GetGwNetworkAddress () const;

  /**
   * \brief Set the initial network number to use during allocation of UT and
   *        UT users.
   * \param addr the initial network number, e.g., 10.3.1.0 (must be different
   *             from network numbers of beam and GW networks)
   * \return true if the operation is successful
   *
   * 255.255.255.0 will be used as the network mask.
   */
  bool SetUtNetworkAddress (Ipv4Address addr);

  /// \return the initial network number of UT and UT users
  Ipv4Address GetUtNetworkAddress () const;

  //\return The device belonging to same network with given device on given node.

  /**
   * Find given device's counterpart (device belonging to same network) device from given node.
   *
   * \param devA Pointer to the device whose counterpart device is found from given node.
   * \param nodeB Pointer to node where given device's counterpart device is searched.
   * \return Pointer to device belonging to same network with given device in given node.
   *         NULL in cast that counterpart device is not found.
   */
  Ptr<NetDevice> FindMatchingDevice ( Ptr<NetDevice> devA, Ptr<Node> nodeB );

  /// \return The device belonging to same network with given device on given node.
  /**
   * Find counterpart (device belonging to same network) devices from given nodes.
   *
   * @param nodeA Pointer to node A where given device's counterpart device is searched.
   * @param nodeB Pointer to node A where given device's counterpart device is searched.
   * @param matchingDevices Pair consisting pointers to found devices. first belongs to nodeA
   *                        and second to nodeB.
   * @return true when counterpart devices are found from given nodes, false in other cases.
   */
  bool FindMatchingDevices ( Ptr<Node> nodeA, Ptr<Node> nodeB, std::pair<Ptr<NetDevice>, Ptr<NetDevice> >& matchingDevices);

  /**
   * Set multicast traffic to source's nwtwork by finding source network utilizing given
   * destination node.
   *
   * Note that all multicast traffic is routed by source through selected device in source node
   * to found network.
   *
   * \param source Pointer to source node of the multicast traffic.
   * \param destination Pointer to destination node where to find matching source network
   */
  void SetMulticastRouteToSourceNetwork (Ptr<Node> source, Ptr<Node> destination);

  /**
   * Construct multicast information from source UT node and group receivers.
   *
   * \param sourceUtNode Pointer to UT source node. When NULL source node is not UT.
   * \param receivers Container of the multicast group receivers.
   * \param beamInfo Beam information to be filled in for multicast group.
   * \param routerUserOutputDev Pointer to router output device for backbone network (GW users). Set to NULL when traffic is
   *        not needed to route backbone network.
   * \return true when multicast traffic shall be routed to source's network.
   */
  bool ConstructMulticastInfo (Ptr<Node> sourceUtNode, NodeContainer receivers, MulticastBeamInfo_t& beamInfo, Ptr<NetDevice>& routerUserOutputDev );
};

} // namespace ns3


#endif /* __SATELLITE_HELPER_H__ */

