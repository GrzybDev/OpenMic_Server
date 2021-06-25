#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QtMultimedia/QAudioFormat>
#include <QtMultimedia/QAudioOutput>


class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);

    void addChunk(QByteArray data);

signals:
private:
    QAudioFormat format;
    QAudioOutput *audio_out;
    QIODevice* audioDevice;
};

#endif // PLAYER_H
