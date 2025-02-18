/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2013-2023 Regents of the University of California.
 *
 * This file is part of ndn-cxx library (NDN C++ library with eXperimental eXtensions).
 *
 * ndn-cxx library is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later version.
 *
 * ndn-cxx library is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
 *
 * You should have received copies of the GNU General Public License and GNU Lesser
 * General Public License along with ndn-cxx, e.g., in COPYING.md file.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * See AUTHORS.md for complete list of ndn-cxx authors and contributors.
 *
 * @author Davide Pesavento <davide.pesavento@lip6.fr>
 */

#ifndef NDN_CXX_NET_NETWORK_MONITOR_IMPL_NOOP_HPP
#define NDN_CXX_NET_NETWORK_MONITOR_IMPL_NOOP_HPP

#include "ndn-cxx/net/network-monitor.hpp"

namespace ndn::net {

class NetworkMonitorImplNoop final : public NetworkMonitorImpl
{
public:
  explicit
  NetworkMonitorImplNoop(boost::asio::io_service&)
  {
  }

  uint32_t
  getCapabilities() const final
  {
    return NetworkMonitor::CAP_NONE;
  }

  shared_ptr<const NetworkInterface>
  getNetworkInterface(const std::string&) const final
  {
    return {};
  }

  std::vector<shared_ptr<const NetworkInterface>>
  listNetworkInterfaces() const final
  {
    return {};
  }
};

} // namespace ndn::net

#endif // NDN_CXX_NET_NETWORK_MONITOR_IMPL_NOOP_HPP
