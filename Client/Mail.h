//
// Created by Filippo Cacciotto on 30/09/2020.
//

#ifndef EDITORCOLLABORATIVO_MAIL_H
#define EDITORCOLLABORATIVO_MAIL_H


#include <string>
#include <curl/curl.h>
#include <ctime>
#include <chrono>
#include <sstream>
#include <iostream>

struct upload_status {
    int lines_read;
};

static const char *payload_text[] = {
        "Date: Mon, 29 Nov 2010 21:54:29 +1100\r\n",
        "To: \r\n",
        "From: progettopds@gmail.com (Collaborative Editor)\r\n",
        "Message-ID: \r\n",
        "Subject: Invite to collaborate\r\n",
        "\r\n",

        "Hi! Join me in the modification of my document! Copy this URI inside your client and let's start collaborating!.\r\n",
        "\r\n",
        "URI: \r\n",
        "\r\nSee you in the editor!\r\n",
        nullptr
};

class Mail {
    static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp);
public:
    static int sendMail(const std::string& receiver, const std::string& uri);
};


#endif //EDITORCOLLABORATIVO_MAIL_H
