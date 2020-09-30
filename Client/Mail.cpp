//
// Created by Filippo Cacciotto on 30/09/2020.
//

#include "Mail.h"

size_t Mail::payload_source(void *ptr, size_t size, size_t nmemb, void *userp) {
    auto *upload_ctx = (struct upload_status *)userp;
    const char *data;

    if((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) {
        return 0;
    }

    data = payload_text[upload_ctx->lines_read];

    if(data) {
        size_t len = strlen(data);
        memcpy(ptr, data, len);
        upload_ctx->lines_read++;

        return len;
    }
    return 0;
}

int Mail::sendMail(const std::string &receiver, const std::string &uri) {

    /*Imposto i campi variabili*/

    /*Utente che invia l'invito*/
    std::string sender = "Sender";                      //(TO DO) qui ci va il nome dell'utente che sta mandando l'invio
    std::string sen = "From: progettopds@gmail.com (" + sender + ")\r\n";
    payload_text[2] = sen.c_str();

    /*Destinatario Invito*/
    std::string rec = "To: " + receiver + "\r\n";
    payload_text[1] = rec.c_str();

    /*ID Mail*/
    std::string id = "Message-ID: <15>\r\n";             //(TO DO) in realtà qui ci andrebbe l'id univoco preso dalla memoria
    payload_text[3] = id.c_str();

    /*URI documento*/
    std::string prov_uri = "URI: " + uri + "\r\n";      //(TO DO) qui ci va l'uri del documento corrente
    payload_text[8] = prov_uri.c_str();

    CURL *curl;
    CURLcode res = CURLE_OK;
    struct curl_slist *recipients = nullptr;
    struct upload_status upload_ctx{};
    upload_ctx.lines_read = 0;

    curl = curl_easy_init();
    if(curl) {
        /* Username e password dell'account */
        curl_easy_setopt(curl, CURLOPT_USERNAME, "progettopds@gmail.com");
        curl_easy_setopt(curl, CURLOPT_PASSWORD, "provaprogetto.123");

        /* URL del server SMTP */
        curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587");

        curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);

        /* TLS: in questo momento l'ho disabilitata, bisogna cambiarla se si vogliono usare i certificati */
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, "progettopds@gmail.com");

        /* Destinatari */
        recipients = curl_slist_append(recipients, receiver.c_str());
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        /* Invio del messaggio */
        res = curl_easy_perform(curl);

        /* Check di eventuali errori */
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        /* Liberazione della lista dei destinatari */
        curl_slist_free_all(recipients);

        /* Cleanup */
        curl_easy_cleanup(curl);
    }
    return (int)res;
}
