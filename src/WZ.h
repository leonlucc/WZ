#ifndef WZ_H
#define WZ_H

class WZ
{
public:
    static const uint16_t SINGLE_RESPONSE_TIME = 1000;
    static const uint8_t WZ_START_TAG = 0Xff;

    struct DATA
    {
        uint16_t HCHO_PPB;
        uint16_t HCHO_UGM3;
    };

    WZ(Stream &);
    void activeMode();
    void passiveMode();
    void requestRead();
    bool read(DATA &data);
    bool readUntil(DATA &data, uint16_t timeout = SINGLE_RESPONSE_TIME);

private:
    enum STATUS
    {
        STATUS_WAITING,
        STATUS_OK
    };
    enum MODE
    {
        MODE_ACTIVE,
        MODE_PASSIVE
    };

    Stream *_stream;
    DATA *_data;
    STATUS _status;
    MODE _mode = MODE_ACTIVE;

    static const uint8_t RAW_DATA_SIZE = 9;
    uint8_t _raw[RAW_DATA_SIZE];

    bool rawAvailable(void);
    bool checksumMatch(uint8_t raw[RAW_DATA_SIZE]);
    void loop();
};

#endif