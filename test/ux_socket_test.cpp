#include "ux_socket.h"

#include <gtest/gtest.h>

#include "socket_mock.h"

using namespace ara::com::ipc;

extern bool shall_succeed;

struct UxSocketTest : public testing::Test
{
    std::unique_ptr<SocketMock> mock_;
    const int valid_return_value = 0;
    const int invalid_return_value = -1;

    UxSocketTest() : mock_{std::make_unique<SocketMock>()}
    {
    }

    ~UxSocketTest()
    {
    }
};

TEST_F(UxSocketTest, OpenUxSocketThenClose)
{
    const int valid_socket_fd = 3;

    EXPECT_CALL(*mock_, socket).WillOnce(testing::Return(valid_socket_fd));
    EXPECT_CALL(*mock_, close);

    UxSocket sock(std::move(mock_));
    EXPECT_EQ(valid_socket_fd, sock.get_socket_fd());
}

TEST_F(UxSocketTest, OpenUxSocketAndThrow)
{
    const int invalid_socket_fd = -1;

    EXPECT_CALL(*mock_, socket).WillOnce(testing::Return(invalid_socket_fd));

    EXPECT_THROW(UxSocket{std::move(mock_)}, std::runtime_error);
}

TEST_F(UxSocketTest, CallUxRemoveThenBind)
{
    EXPECT_CALL(*mock_, socket);
    EXPECT_CALL(*mock_, close);
    EXPECT_CALL(*mock_, remove);
    EXPECT_CALL(*mock_, bind);
    errno = 0;
    UxSocket sock(std::move(mock_));
    sock.bind("");
}

TEST_F(UxSocketTest, CallUxRemoveAndThrow)
{
    EXPECT_CALL(*mock_, socket);
    EXPECT_CALL(*mock_, close);
    EXPECT_CALL(*mock_, remove).WillOnce(testing::Return(invalid_return_value));

    UxSocket sock(std::move(mock_));
    EXPECT_THROW(sock.bind(""), std::runtime_error);
}

TEST_F(UxSocketTest, CallUxRemoveThenBindAndThrow)
{
    EXPECT_CALL(*mock_, socket);
    EXPECT_CALL(*mock_, close);
    EXPECT_CALL(*mock_, remove);
    EXPECT_CALL(*mock_, bind).WillOnce(testing::Return(invalid_return_value));

    UxSocket sock(std::move(mock_));
    EXPECT_THROW(sock.bind(""), std::runtime_error);
}

TEST_F(UxSocketTest, CallUxListen)
{
    EXPECT_CALL(*mock_, socket);
    EXPECT_CALL(*mock_, close);
    EXPECT_CALL(*mock_, listen);

    UxSocket sock(std::move(mock_));
    sock.listen();
}

TEST_F(UxSocketTest, CallUxListenAndThrow)
{
    EXPECT_CALL(*mock_, socket);
    EXPECT_CALL(*mock_, close);
    EXPECT_CALL(*mock_, listen).WillOnce(testing::Return(invalid_return_value));

    UxSocket sock(std::move(mock_));
    EXPECT_THROW(sock.listen(), std::runtime_error);
}

TEST_F(UxSocketTest, CallUxAcceptThenCallItAgainAndThrow)
{
    EXPECT_CALL(*mock_, socket);
    EXPECT_CALL(*mock_, close);
    EXPECT_CALL(*mock_, accept)
        .Times(2)
        .WillOnce(testing::Return(valid_return_value))
        .WillOnce(testing::Return(invalid_return_value));

    UxSocket sock(std::move(mock_));
    EXPECT_EQ(valid_return_value, sock.accept(nullptr, nullptr));
    EXPECT_THROW(sock.accept(nullptr, nullptr), std::runtime_error);
}

TEST_F(UxSocketTest, CallUxConnect)
{
    EXPECT_CALL(*mock_, socket);
    EXPECT_CALL(*mock_, close);
    EXPECT_CALL(*mock_, connect);

    UxSocket sock(std::move(mock_));
    sock.connect("");
}

TEST_F(UxSocketTest, CallUxConnectAndThrow)
{
    EXPECT_CALL(*mock_, socket);
    EXPECT_CALL(*mock_, close);
    EXPECT_CALL(*mock_, connect).WillOnce(testing::Return(invalid_return_value));

    UxSocket sock(std::move(mock_));
    EXPECT_THROW(sock.connect(""), std::runtime_error);
}
