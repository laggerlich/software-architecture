#include "group_message.h"
#include "database.h"
#include "../config/config.h"

#include <Poco/Data/MySQL/Connector.h>
#include <Poco/Data/MySQL/MySQLException.h>
#include <Poco/Data/SessionFactory.h>
#include <Poco/Data/RecordSet.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

#include <sstream>
#include <exception>

using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;

namespace database
{
    void GroupMessage::init()
    {
        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Statement create_stmt_group_message(session);
            create_stmt_group_message << "CREATE TABLE IF NOT EXISTS `GroupMessage` ("
                        << "`id` INT NOT NULL AUTO_INCREMENT,"
                        << "`group_id` INT NOT NULL,"
                        << "`sender_id` INT NOT NULL,"
                        << "`text` VARCHAR(2048) NULL,"
                        << "`create_date` DATETIME NOT NULL,"
                        << "PRIMARY KEY (`id`),"
                        << "CONSTRAINT `fk_group_id`"
                        << "FOREIGN KEY (`group_id`)"
                        << "REFERENCES `Group` (`id`),"
                        << "CONSTRAINT `fk_group_sender_user`"
                        << "FOREIGN KEY (`sender_id`)"
                        << "REFERENCES `User` (`id`));",
                now;

            Statement create_stmt_grp_msg_read(session);
            create_stmt_grp_msg_read << "CREATE TABLE IF NOT EXISTS `GroupMessageRead` ("
                        << "`id` INT NOT NULL AUTO_INCREMENT,"
                        << "`user_id` INT NOT NULL,"
                        << "`group_id` INT NOT NULL,"
                        << "`message_id` INT NOT NULL,"
                        << "PRIMARY KEY (`id`),"
                        << "CONSTRAINT `fk_userRead_id`"
                        << "FOREIGN KEY (`user_id`)"
                        << "REFERENCES `User` (`id`),"
                        << "CONSTRAINT `fk_groupRead_id`"
                        << "FOREIGN KEY (`group_id`)"
                        << "REFERENCES `Group` (`id`),"
                        << "CONSTRAINT `fk_message_id`"
                        << "FOREIGN KEY (`message_id`)"
                        << "REFERENCES `GroupMessage` (`id`),"
                        << "UNIQUE INDEX (group_id, user_id));",
                now;
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

    Poco::JSON::Object::Ptr GroupMessage::toJSON() const
    {
        Poco::JSON::Object::Ptr root = new Poco::JSON::Object();

        Poco::Timestamp tsp = Poco::Timestamp::fromEpochTime(_create_date);

        root->set("id", _id);
        root->set("group_id", _group_id);
        root->set("sender_id", _sender_id);
        root->set("text", _text);
        root->set("create_date", tsp);

        return root;
    }

    void GroupMessage::add_message(long group_id, long sender_id, std::string &text)
    {
        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Poco::Data::Statement insert(session);

            std::string textTmp = text;

            insert << "INSERT INTO GroupMessage (group_id,sender_id,text,create_date) VALUES(?, ?, ?, NOW())",
                use(group_id),
                use(sender_id),
                use(textTmp);

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

    long get_last_unread_id(long user_id, long group_id)
    {
        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Poco::Data::Statement select(session);
            long a;
            select << "SELECT message_id FROM GroupMessageRead where group_id=? and user_id = ?",
                into(a),
                use(group_id),
                use(user_id),
                range(0, 1); //  iterate over result set one row at a time

            select.execute();
            Poco::Data::RecordSet rs(select);
            if (rs.moveFirst()) return a;
        }
        catch (Poco::Data::MySQL::ConnectionException &e)
        {
            std::cout << "connection:" << e.displayText() << std::endl;
            throw;
        }
        catch (Poco::Data::MySQL::StatementException &e)
        {

            std::cout << "statement:" << e.displayText() << std::endl;

            return -1;
        }

        return -1;
    }

    std::vector<GroupMessage> GroupMessage::get_unread(long user_id, long group_id)
    {
        try
        {
            long last_unread = get_last_unread_id(user_id, group_id);

            Poco::Data::Session session = database::Database::get().create_session();
            Statement select(session);
            std::vector<GroupMessage> result;
            GroupMessage a;

            Poco::DateTime tsp;

            select << "SELECT id, group_id,sender_id,text,create_date FROM GroupMessage "
                   << " where group_id = ? "
                   << " and id > ?"
                   << " order by id",
                into(a._id),
                into(a._group_id),
                into(a._sender_id),
                into(a._text),
                into(tsp),
                use(group_id),
                use(last_unread),
                range(0, 1); //  iterate over result set one row at a time

            long last_id = -1;

            while (!select.done())
            {
                if (select.execute()){

                    tsp.makeLocal(3);

                    a._create_date = tsp.timestamp().epochTime();

                    result.push_back(a);

                    last_id = a._id;
                }
            }

            if(last_id != -1)
            {
                try
                {
                    Statement update(session);

                    update << "INSERT INTO GroupMessageRead(group_id,user_id,message_id) "
                        <<"values(?,?,?)"
                        <<"ON DUPLICATE KEY UPDATE message_id = ?",
                        use(group_id),
                        use(user_id),
                        use(last_id),
                        use(last_id),
                        now;
                }
                catch (Poco::Data::MySQL::StatementException &e)
                {
                    std::cout << "statement:" << e.displayText() << std::endl;
                }
            }

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
}