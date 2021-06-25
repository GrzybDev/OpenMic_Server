#include "player.h"

Player::Player(QObject *parent) : QObject(parent)
{
    format.setSampleRate(48000);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");

    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();

    if (!info.isFormatSupported(format))
    {
        format = info.nearestFormat(format);
    }

    audio_out = new QAudioOutput(format, NULL);
    audioDevice = audio_out->start();
}

void Player::addChunk(QByteArray data) {
    audioDevice->write(data);
}
