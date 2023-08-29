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
 */

#ifndef NDN_CXX_SECURITY_PIB_IDENTITY_CONTAINER_HPP
#define NDN_CXX_SECURITY_PIB_IDENTITY_CONTAINER_HPP

#include "ndn-cxx/security/pib/identity.hpp"

#include <set>
#include <unordered_map>

namespace ndn::security::pib {

class PibImpl;

/**
 * @brief Container of identities of a PIB.
 *
 * The container is used to search/enumerate the identities in a PIB.
 * It can be created only by the Pib class.
 *
 * @sa Pib::getIdentities()
 */
class IdentityContainer : noncopyable
{
private:
  using NameSet = std::set<Name>;

public:
  class const_iterator : public boost::forward_iterator_helper<const_iterator, const Identity>
  {
  public:
    const_iterator() = default;

    Identity
    operator*() const
    {
      BOOST_ASSERT(m_container != nullptr);
      return m_container->get(*m_it);
    }

    const_iterator&
    operator++()
    {
      ++m_it;
      return *this;
    }

    friend bool
    operator==(const const_iterator& lhs, const const_iterator& rhs) noexcept
    {
      return lhs.equals(rhs);
    }

  private:
    const_iterator(NameSet::const_iterator it, const IdentityContainer& container) noexcept
      : m_it(it)
      , m_container(&container)
    {
    }

    bool
    equals(const const_iterator& other) const noexcept;

  private:
    NameSet::const_iterator m_it;
    const IdentityContainer* m_container = nullptr;

    friend IdentityContainer;
  };

  using iterator = const_iterator;

public:
  const_iterator
  begin() const noexcept
  {
    return {m_identityNames.begin(), *this};
  }

  const_iterator
  end() const noexcept
  {
    return {};
  }

  const_iterator
  find(const Name& identity) const;

  /**
   * @brief Check whether the container is empty.
   */
  [[nodiscard]] bool
  empty() const noexcept
  {
    return m_identityNames.empty();
  }

  /**
   * @brief Return the number of identities in the container.
   */
  size_t
  size() const noexcept
  {
    return m_identityNames.size();
  }

  /**
   * @brief Add @p identity into the container.
   */
  Identity
  add(const Name& identity);

  /**
   * @brief Remove @p identity from the container.
   */
  void
  remove(const Name& identity);

  /**
   * @brief Return an identity by name.
   * @throw Pib::Error The identity does not exist.
   */
  Identity
  get(const Name& identity) const;

  /**
   * @brief Reset the state of the container.
   *
   * This clears all cached information and reloads the identity names from the PIB backend.
   */
  void
  reset();

  /**
   * @brief Check if the container is consistent with the backend storage.
   * @note This method is heavyweight and should be used in debugging mode only.
   */
  bool
  isConsistent() const;

NDN_CXX_PUBLIC_WITH_TESTS_ELSE_PRIVATE: // private interface for Pib
  /**
   * @brief Create identity container.
   * @param pibImpl The PIB backend implementation.
   */
  explicit
  IdentityContainer(shared_ptr<PibImpl> pibImpl);

NDN_CXX_PUBLIC_WITH_TESTS_ELSE_PRIVATE:
  // cache of loaded IdentityImpl
  mutable std::unordered_map<Name, shared_ptr<IdentityImpl>> m_identities;

private:
  NameSet m_identityNames;
  const shared_ptr<PibImpl> m_pib;

  friend class Pib;
};

} // namespace ndn::security::pib

#endif // NDN_CXX_SECURITY_PIB_IDENTITY_CONTAINER_HPP
