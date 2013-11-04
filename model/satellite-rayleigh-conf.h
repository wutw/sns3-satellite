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
 * Author: Frans Laakso <frans.laakso@magister.fi>
 */

#ifndef SAT_RAYLEIGH_CONF_H
#define SAT_RAYLEIGH_CONF_H

#include "satellite-fader-conf.h"

namespace ns3 {

/**
 * \brief A configuration class for Rayleigh model
 *
 */
class SatRayleighConf : public SatFaderConf
{
public:

  /**
   * \brief Default Rayleigh parameter count
   */
  static const uint32_t DEFAULT_RAYLEIGH_PARAMETER_COUNT = 2;

  /**
   * \brief NS-3 function for type id
   * \return
   */
  static TypeId GetTypeId (void);

  /**
   * \brief Constructor
   */
  SatRayleighConf ();

  /**
   * \brief Destructor
   */
  virtual ~SatRayleighConf () {}

  /**
   * \brief Function for getting the Rayleigh parameters
   * \param set parameter set
   * \return Rayleigh parameter values
   */
  std::vector<std::vector<double> > GetParameters (uint32_t set);

private:

  /**
   * \brief Number of parameters sets
   */
  uint32_t m_elevationCount;

  /**
   * \brief Number of states
   */
  uint32_t m_stateCount;

  /**
   * \brief Rayleigh model parameters
   */
  std::vector<std::vector<std::vector<double> > > m_rayleighParameters;
};

} // namespace ns3

#endif /* SAT_RAYLEIGH_CONF_H */