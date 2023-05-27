#ifndef GROUP_H
#define GROUP_H

#include <string>
#include <vector>
#include "Poco/JSON/Object.h"
#include <optional>
#include <ctime>

namespace database
{
    class Group{
        private:
            long _id;
            std::string _name;
            long _author_id;
            time_t _create_date;
            bool _able_write;

        public:
            static void init();

            static Group save_group_to_mysql(std::string group_name, long author_id, bool able_write);

            Poco::JSON::Object::Ptr toJSON() const;

            long groupId();
    };
}

#endif