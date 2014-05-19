/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil -*- */
/**
 * Copyright (c) 2013-2014,  Regents of the University of California.
 * All rights reserved.
 *
 * This file is part of ndn-cxx library (NDN C++ library with eXperimental eXtensions).
 * See AUTHORS.md for complete list of ndn-cxx authors and contributors.
 *
 * This file licensed under New BSD License.  See COPYING for detailed information about
 * ndn-cxx library copyright, permissions, and redistribution restrictions.
 */

#ifndef NDN_MANAGEMENT_NFD_FACE_FLAGS_HPP
#define NDN_MANAGEMENT_NFD_FACE_FLAGS_HPP

namespace ndn {
namespace nfd {

/**
 * \ingroup management
 * \enum FaceFlags
 * \brief provides additional information about a face
 */
enum {
  /** \brief face is local (for scope control purpose)
   */
  FACE_IS_LOCAL = 1,
  /** \brief face is created on demand (accepted incoming connection,
   *         not initiated outgoing connection)
   */
  FACE_IS_ON_DEMAND = 2
  // FACE_? = 4
  // FACE_? = 8
};

/**
 * \ingroup management
 * \brief implements getters to each face flag
 *
 * \tparam T class containing a FaceFlags field and implements
 *           `FaceFlags getFlags() const` method
 */
template<typename T>
class FaceFlagsTraits
{
public:
  bool
  isLocal() const
  {
    return static_cast<const T*>(this)->getFlags() & FACE_IS_LOCAL;
  }

  bool
  isOnDemand() const
  {
    return static_cast<const T*>(this)->getFlags() & FACE_IS_ON_DEMAND;
  }
};

} // namespace nfd
} // namespace ndn

#endif // NDN_MANAGEMENT_NFD_FACE_FLAGS_HPP