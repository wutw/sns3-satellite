/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/satellite-module.h"
#include "ns3/applications-module.h"

using namespace ns3;

/**
* \ingroup satellite
*
* \brief Example for Markov model class logic.
*
*/
NS_LOG_COMPONENT_DEFINE ("sat-markov-logic-example");

static double g_elevation = 45;
static double g_velocity = 0;

static double GetElevation ()
{
   return g_elevation;
}

static void SetElevation (double elevation)
{
   g_elevation = elevation;
}

static double GetVelocity ()
{
   return g_velocity;
}

static void SetVelocity (double velocity)
{
   g_velocity = velocity;
}

int
main (int argc, char *argv[])
{
  /// Enable info logs
  LogComponentEnable ("sat-markov-logic-example", LOG_LEVEL_INFO);
  LogComponentEnable ("SatMarkovContainer", LOG_LEVEL_INFO);
  LogComponentEnable ("SatMarkovModel", LOG_LEVEL_INFO);
  LogComponentEnable ("SatMarkovConf", LOG_LEVEL_INFO);

  /// Create default Markov & Loo configurations
  Ptr<SatMarkovConf> markovConf = CreateObject<SatMarkovConf> ();

  SatBaseFading::ElevationCallback elevationCb = MakeCallback (&GetElevation);
  SatBaseFading::VelocityCallback velocityCb = MakeCallback (&GetVelocity);

  /// Create fading container based on default configuration
  Ptr<SatMarkovContainer> markovContainer = CreateObject<SatMarkovContainer> (markovConf,elevationCb,velocityCb);

  Address macAddress;

  /// Run simulation
  Simulator::Schedule (Time ("5ms"), &SetVelocity, 0);
  Simulator::Schedule (Time ("10ms"), &SatMarkovContainer::DoGetFading, markovContainer, macAddress, SatEnums::FORWARD_USER_CH);
  Simulator::Schedule (Time ("30ms"), &SatMarkovContainer::DoGetFading, markovContainer, macAddress, SatEnums::FORWARD_USER_CH);
  Simulator::Schedule (Time ("45ms"), &SetElevation, 55);
  Simulator::Schedule (Time ("50ms"), &SatMarkovContainer::DoGetFading, markovContainer, macAddress, SatEnums::FORWARD_USER_CH);
  Simulator::Schedule (Time ("60ms"), &SatMarkovContainer::DoGetFading, markovContainer, macAddress, SatEnums::FORWARD_USER_CH);
  Simulator::Schedule (Time ("90ms"), &SatMarkovContainer::DoGetFading, markovContainer, macAddress, SatEnums::FORWARD_USER_CH);
  Simulator::Schedule (Time ("95ms"), &SetElevation, 75);
  Simulator::Schedule (Time ("100ms"), &SatMarkovContainer::DoGetFading, markovContainer, macAddress, SatEnums::FORWARD_USER_CH);
  Simulator::Schedule (Time ("130ms"), &SatMarkovContainer::DoGetFading, markovContainer, macAddress, SatEnums::FORWARD_USER_CH);
  Simulator::Schedule (Time ("200ms"), &SatMarkovContainer::DoGetFading, markovContainer, macAddress, SatEnums::FORWARD_USER_CH);

  Simulator::Run ();
  Simulator::Destroy ();

  return 0;
}