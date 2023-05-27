#ifndef GROUP_USER_H
#define GROUP_USER_H

#include <string>
#include <vector>
#include "Poco/JSON/Object.h"
#include <optional>
#include <ctime>

namespace database
{
    class GroupUser{
        private:
            long _id;
            long _group_id;
            long _user_id;
            bool _is_moder;
            bool _is_admin;


        public:
            static void init();

            static GroupUser add_user(long group_id, long user_id,bool is_admin, bool is_moder);

            Poco::JSON::Object::Ptr toJSON() const;
    };
}

#endif