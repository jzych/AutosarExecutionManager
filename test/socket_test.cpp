#include <gtest/gtest.h>
#include "socket.h"

using namespace ara::com::ipc;

extern bool shall_succeed;

struct SocketTest : public testing::Test
{
    Socket* ux_sock_impl_;
    const int valid_value = 0;
    const int invalid_value = -1;

    SocketTest()
    {
        ux_sock_impl_ = new Socket;
    }

    ~SocketTest()
    {
        delete ux_sock_impl_;
    }
};

TEST_F(SocketTest, SocketSuccess)
{
    shall_succeed = true;
    EXPECT_EQ(valid_value, ux_sock_impl_->socket(0,0,0));
}

TEST_F(SocketTest, SocketFailure)
{
    shall_succeed = false;
    EXPECT_EQ(invalid_value, ux_sock_impl_->socket(0,0,0));
}

TEST_F(SocketTest, CloseSuccess)
{
    shall_succeed = true;
    EXPECT_EQ(valid_value, ux_sock_impl_->close(0));
}

TEST_F(SocketTest, CloseFailure)
{
    shall_succeed = false;
    EXPECT_EQ(invalid_value, ux_sock_impl_->close(0));
}

TEST_F(SocketTest, RemoveSuccess)
{
    shall_succeed = true;
    EXPECT_EQ(valid_value, ux_sock_impl_->remove(""));
}

TEST_F(SocketTest, RemoveFailure)
{
    shall_succeed = false;
    EXPECT_EQ(invalid_value, ux_sock_impl_->remove(""));
}

TEST_F(SocketTest, BindSuccess)
{
    shall_succeed = true;
    EXPECT_EQ(valid_value, ux_sock_impl_->bind(0, nullptr, 0));
}

TEST_F(SocketTest, BindFailure)
{
    shall_succeed = false;
    EXPECT_EQ(invalid_value, ux_sock_impl_->bind(0, nullptr, 0));
}

TEST_F(SocketTest, ListenSuccess)
{
    shall_succeed = true;
    EXPECT_EQ(valid_value, ux_sock_impl_->listen(0,0));
}

TEST_F(SocketTest, ListenFailure)
{
    shall_succeed = false;
    EXPECT_EQ(invalid_value, ux_sock_impl_->listen(0,0));
}

TEST_F(SocketTest, AcceptSuccess)
{
    shall_succeed = true;
    EXPECT_EQ(valid_value, ux_sock_impl_->accept(0, nullptr, nullptr));
}

TEST_F(SocketTest, AcceptFailure)
{
    shall_succeed = false;
    EXPECT_EQ(invalid_value, ux_sock_impl_->accept(0, nullptr, nullptr));
}

TEST_F(SocketTest, ConnectSuccess)
{
    shall_succeed = true;
    EXPECT_EQ(valid_value, ux_sock_impl_->connect(0, nullptr, 0));
}

TEST_F(SocketTest, ConnectFailure)
{
    shall_succeed = false;
    EXPECT_EQ(invalid_value, ux_sock_impl_->connect(0, nullptr, 0));
}