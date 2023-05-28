#include "p2p.h"
#include "database.h"
#include "../config/config.h"

#include <Poco/Data/MySQL/Connector.h>
#include <Poco/Data/MySQL/MySQLException.h>
#include "Poco/Data/MySQL/MySQL.h"
#include <Poco/Data/RecordSet.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

#include <sstream>
#include <exception>
#include <ctime>

using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;

namespace database
{

    void P2P::init()
    {
        try
        {

            Poco::Data::Session session = database::Database::get().create_session();
            Statement create_stmt(session);
            create_stmt << "CREATE TABLE IF NOT EXISTS `P2P` ("
                        << "`id` INT NOT NULL AUTO_INCREMENT,"
                        << "`sender_id` INT NOT NULL,"
                        << "`receiver_id` INT NOT NULL,"
                        << "`text` VARCHAR(2048) NULL,"
                        << "`create_date` DATETIME NOT NULL,"
                        << "`is_read` BOOLEAN NOT NULL,"
                        << "PRIMARY KEY (`id`));",
                now;

        }

        catch (Poco::Data::MySQL::ConnectionException &e)
        {
            std::cout << "connection:" << e.what() << std::endl;
            throw;
        }
        catch (Poco::Data::MySQL::StatementException &e)
        {

            std::cout << "statement:" << e.what() << std::endl;
            throw;
        }
    }

    Poco::JSON::Object::Ptr P2P::toJSON() const
    {
        Poco::JSON::Object::Ptr root = new Poco::JSON::Object();

        Poco::Timestamp tsp = Poco::Timestamp::fromEpochTime(_create_date);

        root->set("id", _id);
        root->set("sender_id", _sender_id);
        root->set("receiver_id", _receiver_id);
        root->set("text", _text);
        root->set("create_date", tsp);
        root->set("is_read", _is_read);

        return root;
    }

    P2P P2P::fromJSON(const std::string &str)
    {
        P2P p2p;
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(str);
        Poco::JSON::Object::Ptr object = result.extract<Poco::JSON::Object::Ptr>();

        p2p.id() = object->getValue<long>("id");
        p2p.sender_id() = object->getValue<long>("sender_id");
        p2p.receiver_id() = object->getValue<long>("receiver_id");
        p2p.text() = object->getValue<std::string>("text");
        p2p.create_date() = object->getValue<time_t>("create_date");
        p2p.is_read() = object->getValue<bool>("is_read");

        return p2p;
    }

    void P2P::send_p2p(long sender_id, long receiver_id,const std::string &text)
    {
        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Poco::Data::Statement insert(session);

            bool isFalse = false;

            std::string textTmp = text;

            insert << "INSERT INTO P2P (sender_id,receiver_id,text,create_date,is_read) VALUES(?, ?, ?, NOW(), ?)",
                use(sender_id),
                use(receiver_id),
                use(textTmp),
                use(isFalse);

            insert.execute();
        }

        catch (Poco::Data::MySQL::ConnectionException &e)
        {
            std::cout << "connection:" << e.displayText() << std::endl;
        }
        catch (Poco::Data::MySQL::StatementException &e)
        {

            std::cout << "statement:" << e.displayText() << std::endl;
        }
    }

    std::vector<P2P> P2P::get_p2p_messages(long sender_id, long receiver_id)
    {
        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Statement select(session);
            std::vector<P2P> result;
            P2P a;

            Poco::DateTime tsp;

            select << "SELECT id, sender_id, receiver_id, text,create_date, is_read FROM P2P "
                   << " where receiver_id = ? "
                   << " and sender_id = ? "
                   << " and is_read = FALSE "
                   << " order by id",
                into(a._id),
                into(a._sender_id),
                into(a._receiver_id),
                into(a._text),
                into(tsp),
                into(a._is_read),
                use(receiver_id),
                use(sender_id),
                range(0, 1); //  iterate over result set one row at a time

            long last_id = 0;

            while (!select.done())
            {
                if (select.execute()){

                    tsp.makeLocal(3);

                    a._create_date = tsp.timestamp().epochTime();

                    result.push_back(a);

                    last_id = a.id();
                }
            }

            Statement update(session);

            update << "update P2P "
                << " set is_read = TRUE "
                << " where is_read = FALSE "
                << " and id <= ? "
                << " and receiver_id = ? "
                << " and sender_id = ? ",
                use(last_id),
                use(receiver_id),
                use(sender_id),
                now;

            return result;
        }

        catch (Poco::Data::MySQL::ConnectionException &e)
        {
            std::cout << "connection:" << e.displayText() << std::endl;
            throw;
        }
        catch (Poco::Data::MySQL::StatementException &e)
        {

            std::cout << "statement:" << e.displayText() << std::endl;
            throw;
        }
    }

    long P2P::get_id() const
    {
        return _id;
    }

    long &P2P::id()
    {
        return _id;
    }

    long P2P::get_sender_id() const
    {
        return _sender_id;
    }

    long &P2P::sender_id()
    {
        return _sender_id;
    }

    long P2P::get_receiver_id() const
    {
        return _receiver_id;
    }

    long &P2P::receiver_id()
    {
        return _receiver_id;
    }

    const std::string &P2P::get_text() const
    {
        return _text;
    }

    std::string &P2P::text()
    {
        return _text;
    }

    const time_t &P2P::get_create_date() const
    {
        return _create_date;
    }

    time_t &P2P::create_date()
    {
        return _create_date;
    }

    const bool &P2P::get_is_read() const
    {
        return _is_read;
    }

    bool &P2P::is_read()
    {
        return _is_read;
    }

}