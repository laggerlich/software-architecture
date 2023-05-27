#ifndef AUTHOR_H
#define AUTHOR_H

#include <string>
#include <vector>
#include "Poco/JSON/Object.h"
#include <optional>
#include <ctime>

namespace database
{
    class P2P{
        private:
            long _id;
            long _sender_id;
            long _receiver_id;
            std::string _text;
            time_t _create_date;
            bool _is_read;

        public:

            long             get_id() const;
            long             get_sender_id() const;
            long             get_receiver_id() const;
            const std::string &get_text() const;
            const time_t &get_create_date() const;
            const bool &get_is_read() const;

            long&        id();
            long&        sender_id();
            long&        receiver_id();
            std::string &text();
            time_t      &create_date();
            bool        &is_read();

            Poco::JSON::Object::Ptr toJSON() const;

            static void init();
            static void send_p2p(long sender_id, long receiver_id,const std::string &text);
            static std::vector<P2P> get_p2p_messages(long sender_id,long receiver_id);

            static P2P fromJSON(const std::string & str);


    };
}

#endif