#include "group_user.h"
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
    void GroupUser::init()
    {
        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Statement create_stmt(session);
            create_stmt << "CREATE TABLE IF NOT EXISTS `GroupUser` ("
                        << "`id` INT NOT NULL AUTO_INCREMENT,"
                        << "`group_id` INT NOT NULL,"
                        << "`user_id` INT NOT NULL,"
                        << "`is_moder` BOOLEAN NOT NULL,"
                        << "`is_admin` BOOLEAN NOT NULL,"
                        << "PRIMARY KEY (`id`),"
                        << "CONSTRAINT `fk_groupUser_id`"
                        << "FOREIGN KEY (`group_id`)"
                        << "REFERENCES `Group` (`id`),"
                        << "CONSTRAINT `fk_user_id`"
                        << "FOREIGN KEY (`user_id`)"
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

    Poco::JSON::Object::Ptr GroupUser::toJSON() const
    {
        Poco::JSON::Object::Ptr root = new Poco::JSON::Object();

        root->set("id", _id);
        root->set("group_id", _group_id);
        root->set("user_id", _user_id);
        root->set("is_moder", _is_moder);
        root->set("is_admin", _is_admin);

        return root;
    }

    GroupUser GroupUser::add_user(long group_id, long user_id,bool is_admin, bool is_moder)
    {
        try
        {
            Poco::Data::Session session = database::Database::get().create_session();
            Poco::Data::Statement insert(session);

            GroupUser gu;

            insert << "INSERT INTO GroupUser (group_id,user_id,is_admin,is_moder) VALUES(?, ?, ?, ?)",
                use(group_id),
                use(user_id),
                use(is_admin),
                use(is_moder);

            insert.execute();

            Poco::Data::Statement select(session);
            select << "SELECT LAST_INSERT_ID()",
                into(gu._id),
                range(0, 1); //  iterate over result set one row at a time

            if (!select.done())
            {
                select.execute();
            }

            gu._group_id = group_id;
            gu._user_id = user_id;
            gu._is_admin = is_admin;
            gu._is_moder = is_moder;

            return gu;
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