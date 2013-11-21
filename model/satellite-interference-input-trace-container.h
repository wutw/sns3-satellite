/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2013 Magister Solutions Ltd.
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
 * Author: Frans Laakso <frans.laakso@magister.fi>
 */
#ifndef SATELLITE_INTERFERENCE_INPUT_TRACE_CONTAINER_H
#define SATELLITE_INTERFERENCE_INPUT_TRACE_CONTAINER_H

#include "satellite-base-trace-container.h"
#include "ns3/satellite-input-fstream-double-container.h"
#include "satellite-enums.h"
#include "ns3/mac48-address.h"

namespace ns3 {

/**
 * \ingroup satellite
 *
 * \brief Class for interference input trace container
 */
class SatInterferenceInputTraceContainer : public SatBaseTraceContainer
{
public:

  /**
   * \brief typedef for map key
   */
  typedef std::pair<Address,SatEnums::ChannelType_t> key_t;

  /**
   * \brief typedef for map of containers
   */
  typedef std::map <key_t, Ptr<SatInputFileStreamDoubleContainer> > container_t;

  /**
   * \brief Constructor
   */
  SatInterferenceInputTraceContainer ();

  /**
   * \brief Destructor
   */
  ~SatInterferenceInputTraceContainer ();

  /**
   * \brief NS-3 type id function
   * \return type id
   */
  static TypeId GetTypeId (void);

  /**
   *  \brief Do needed dispose actions.
   */
  void DoDispose ();

  /**
   * \brief Function for adding the node to the map
   * \param key key
   */
  void AddNode (std::pair<Address,SatEnums::ChannelType_t> key);

  /**
   * \brief Function for finding the container matching the key
   * \param key key
   * \return matching container
   */
  Ptr<SatInputFileStreamDoubleContainer> FindNode (key_t key);

  /**
   * \brief Function for getting the interference density
   * \param key key
   * \return Interference density
   */
  double GetInterferenceDensity (key_t key);

  /**
   * \brief Function for getting the Rx power density
   * \param key key
   * \return Rx power density
   */
  double GetRxPowerDensity (key_t key);

private:

  /**
   * \brief Function for resetting the variables
   */
  void Reset ();

  /**
   * \brief Map for containers
   */
  container_t m_container;

  /**
   * \brief Current index number
   */
  uint32_t m_index;

  /**
   * \brief Path to simulator root folder
   */
  std::string m_simulatorRootPath;
};

} // namespace ns3

#endif /* SATELLITE_INTERFERENCE_INPUT_TRACE_CONTAINER_H */
