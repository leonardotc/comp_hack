/**
 * @file libcomp/src/TcpServer.h
 * @ingroup libcomp
 *
 * @author COMP Omega <compomega@tutanota.com>
 *
 * @brief Base TCP/IP server class.
 *
 * This file is part of the COMP_hack Library (libcomp).
 *
 * Copyright (C) 2012-2016 COMP_hack Team <compomega@tutanota.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIBCOMP_SRC_TCPSERVER_H
#define LIBCOMP_SRC_TCPSERVER_H

// libcomp Includes
#include "String.h"

// Boost ASIO Includes
#include "PushIgnore.h"
#include <asio.hpp>
#include "PopIgnore.h"

// Standard C++ Includes
#include <memory>
#include <thread>

// OpenSSL Includes
#include <openssl/dh.h>

namespace libcomp
{

class TcpConnection;

class TcpServer
{
public:
    TcpServer(String listenAddress, int port);
    virtual ~TcpServer();

    virtual int Start();

    static DH* GenerateDiffieHellman();
    static DH* LoadDiffieHellman(const String& prime);
    static DH* LoadDiffieHellman(const std::vector<char>& data);
    static DH* LoadDiffieHellman(const void *pData, size_t dataSize);
    static std::vector<char> SaveDiffieHellman(const DH *pDiffieHellman);
    static DH* CopyDiffieHellman(const DH *pDiffieHellman);

protected:
    virtual std::shared_ptr<TcpConnection> CreateConnection(
        asio::ip::tcp::socket& socket);

    const DH* GetDiffieHellman() const;

    void AcceptHandler(asio::error_code errorCode,
        asio::ip::tcp::socket& socket);
private:
    asio::io_service mService;
    asio::ip::tcp::acceptor mAcceptor;

    std::thread mServiceThread;
    std::list<std::shared_ptr<TcpConnection>> mConnections;

    DH *mDiffieHellman;

    String mListenAddress;
    int mPort;
};

} // namespace libcomp

#endif // LIBCOMP_SRC_TCPSERVER_H
