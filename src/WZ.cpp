#include <Arduino.h>
#include <Stream.h>
#include "WZ.h"

WZ::WZ(Stream &stream)
{
    this->_stream = &stream;
}

// Active mode. Default mode after power up.
void WZ::activeMode()
{
    uint8_t command[] = {0xFF, 0x01, 0x78, 0x40, 0x00, 0x00, 0x00, 0x00, 0x47};
    _stream->write(command, sizeof(command));
    _mode = MODE_ACTIVE;
}

// Passive mode.
void WZ::passiveMode()
{
    uint8_t command[] = {0xFF, 0x01, 0x78, 0x41, 0x00, 0x00, 0x00, 0x00, 0x46};
    _stream->write(command, sizeof(command));
    _mode = MODE_PASSIVE;
}

// Request read in Passive Mode.
void WZ::requestRead()
{
    uint8_t command[] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
    _stream->write(command, sizeof(command));
}

// Non-blocking function for parse response.
bool WZ::read(DATA &data)
{
    _data = &data;
    loop();

    return _status == STATUS_OK;
}

// Blocking function for parse response. Default timeout is 1s.
bool WZ::readUntil(DATA &data, uint16_t timeout)
{
    _data = &data;
    uint32_t start = millis();
    do
    {
        loop();
        if (_status == STATUS_OK)
            break;
    } while (millis() - start < timeout);

    return _status == STATUS_OK;
}

bool WZ::rawAvailable(void)
{
    if (!_stream->available())
    {
        return false;
    }
    while ((_stream->peek() != WZ_START_TAG) && _stream->available())
    {
        _stream->read();
    }
    if (_stream->available() < RAW_DATA_SIZE)
    {
        return false;
    }

    return true;
}

bool WZ::checksumMatch(uint8_t raw[RAW_DATA_SIZE])
{
    uint8_t checksum = raw[RAW_DATA_SIZE - 1];
    uint8_t sum = 0;
    for (int i = 1; i < RAW_DATA_SIZE - 1; i++)
        sum += raw[i];
    sum = (~sum) + 1;

    return checksum == sum;
}

void WZ::loop()
{
    _status = STATUS_WAITING;
    if (rawAvailable())
    {
        _stream->readBytes(_raw, RAW_DATA_SIZE);

        if (checksumMatch(_raw))
        {
            _status = STATUS_OK;

            if (_mode == MODE_ACTIVE)
            {
                _data->HCHO_PPB = makeWord(_raw[4], _raw[5]);
                _data->HCHO_UGM3 = 0; // no value returned
            }
            else
            {
                _data->HCHO_PPB = makeWord(_raw[6], _raw[7]);
                _data->HCHO_UGM3 = makeWord(_raw[2], _raw[3]);
            }
        }
        else
            _stream->flush();
    }
}