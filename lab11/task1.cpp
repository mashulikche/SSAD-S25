#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Codec {
public:
    virtual void decode(const string& fileName) = 0;
    virtual ~Codec() = default;
};

class MP3Codec : public Codec {
public:
    void decode(const string& fileName) override {
        cout << "Playing " << fileName << " using MP3 codec." << endl;
    }
};

class WAVCodec : public Codec {
public:
    void decode(const string& fileName) override {
        cout << "Playing " << fileName << " using WAV codec." << endl;
    }
};

class FLACCodec : public Codec {
public:
    void decode(const string& fileName) override {
        cout << "Playing " << fileName << " using FLAC codec." << endl;
    }
};

class MusicPlayer {
protected:
    unique_ptr<Codec> codec;
    string playerType;

public:
    MusicPlayer(unique_ptr<Codec> codec, const string& type)
            : codec(move(codec)), playerType(type) {}

    virtual void start(const string& fileName) {
        cout << "Started " << playerType << " Player..." << endl;
        codec->decode(fileName);
    }

    virtual ~MusicPlayer() = default;
};

class JazzPlayer : public MusicPlayer {
public:
    JazzPlayer(unique_ptr<Codec> codec)
            : MusicPlayer(move(codec), "Jazz") {}
};

class PopPlayer : public MusicPlayer {
public:
    PopPlayer(unique_ptr<Codec> codec)
            : MusicPlayer(move(codec), "Pop") {}
};

class RockPlayer : public MusicPlayer {
public:
    RockPlayer(unique_ptr<Codec> codec)
            : MusicPlayer(move(codec), "Pop") {}
};


int main() {
    unique_ptr<MusicPlayer> popMP3Player =
            make_unique<PopPlayer>(make_unique<MP3Codec>());

    unique_ptr<MusicPlayer> jazzMP3Player =
            make_unique<JazzPlayer>(make_unique<MP3Codec>());

    unique_ptr<MusicPlayer> popWAVPlayer =
            make_unique<PopPlayer>(make_unique<WAVCodec>());

    unique_ptr<MusicPlayer> rockFLACPlayer =
            make_unique<RockPlayer>(make_unique<FLACCodec>());

    popMP3Player->start("pop_song_1.mp3");
    jazzMP3Player->start("jazz_song.mp3");
    popWAVPlayer->start("pop_song_2.wav");
    rockFLACPlayer->start("rock_song.flac");
    return 0;
}