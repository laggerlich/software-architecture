#include "group.h"
#include "group_user.h"
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
    void Group::init()
    {
        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Statement create_stmt(session);
            create_stmt << "CREATE TABLE IF NOT EXISTS `Group` ("
                        << "`id` INT NOT NULL AUTO_INCREMENT,"
                        << "`name` VARCHAR(256) NOT NULL,"
                        << "`author_id` INT NOT NULL,"
                        << "`create_date` DATETIME NOT NULL,"
                        << "`able_write` BOOLEAN NULL,"
                        << "PRIMARY KEY (`id`),"
                        << "CONSTRAINT `fk_author_user`"
                        << "FOREIGN KEY (`author_id`)"
                        << "REFERENCES `User` (`id`));",
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

    Poco::JSON::Object::Ptr Group::toJSON() const
    {
        Poco::JSON::Object::Ptr root = new Poco::JSON::Object();

        Poco::Timestamp tsp = Poco::Timestamp::fromEpochTime(_create_date);

        root->set("id", _id);
        root->set("name", _name);
        root->set("author_id", _author_id);
        root->set("create_date", tsp);
        root->set("able_write", _able_write);

        return root;
    }

    Group Group::save_group_to_mysql(std::string group_name, long author_id, bool able_write)
    {
        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Poco::Data::Statement insert(session);

            Group grp;

            insert << "INSERT INTO `Group` (name,author_id,create_date,able_write) VALUES(?, ?, NOW(), ?)",
                use(group_name),
                use(author_id),
                use(able_write);

            insert.execute();

            Poco::Data::Statement select_id(session);
            select_id << "SELECT LAST_INSERT_ID()",
                into(grp._id),
                range(0, 1); //  iterate over result set one row at a time

            if (!select_id.done())
            {
                select_id.execute();
            }

            Poco::DateTime tsp;

            Poco::Data::Statement select_grp(session);
            select_grp << "SELECT create_date from `Group` where id = ?",
                into(tsp),
                use(grp._id),
                range(0, 1); //  iterate over result set one row at a time

            if (!select_grp.done())
            {
                select_grp.execute();
            }

            grp._create_date = tsp.timestamp().epochTime();
            grp._able_write = able_write;
            grp._author_id = author_id;
            grp._name = group_name;

            return grp;
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

    long Group::groupId(){
        return _id;
    }

}