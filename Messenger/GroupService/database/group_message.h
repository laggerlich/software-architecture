#ifndef GROUP_MESSAGE_H
#define GROUP_MESSAGE_H

#include <string>
#include <vector>
#include "Poco/JSON/Object.h"
#include <optional>
#include <ctime>

namespace database
{
    class GroupMessage{
        private:
            long _id;
            long _group_id;
            long _sender_id;
            std::string _text;
            time_t _create_date;

        public:
            static void init();
            static void add_message(long group_id, long sender_id, std::string &text);
            static std::vector<GroupMessage> get_unread(long user_id, long group_id);

            Poco::JSON::Object::Ptr toJSON() const;

    };
}

#endif