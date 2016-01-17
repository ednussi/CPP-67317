cc = g++
cppflag = -std=c++11 -Wextra -Wall -g
OBJECTS = MIR.o Rankable.o Song.o RankableSong.o RankableLyricSong.o RankableInstrumentalSong.o \
SongDataBase.o SongMatchingParams.o SortHelper.o Parser.o

all: MIR

MIR: $(OBJECTS)

	$(cc) $(cppflag) $(OBJECTS) -o MIR

MIR.o: MIR.cpp Parser.h
	$(cc) -c $(cppflag) MIR.cpp

Rankable.o: Rankable.h Rankable.cpp
	$(cc) -c $(cppflag) Rankable.cpp

Song.o: Song.h Song.cpp
	$(cc) -c $(cppflag) Song.cpp

RankableSong.o: RankableSong.h RankableSong.cpp Song.h Rankable.h
	$(cc) -c $(cppflag) RankableSong.cpp

RankableLyricSong.o: RankableLyricSong.h RankableLyricSong.cpp RankableSong.h
	$(cc) -c $(cppflag) RankableLyricSong.cpp

RankableInstrumentalSong.o: RankableInstrumentalSong.h RankableInstrumentalSong.cpp RankableSong.h
	$(cc) -c $(cppflag) RankableInstrumentalSong.cpp

SongMatchingParams.o: SongMatchingParams.h SongMatchingParams.cpp
	$(cc) -c $(cppflag) SongMatchingParams.cpp

SongDataBase.o: SongDataBase.h SongDataBase.cpp RankableSong.h SongMatchingParams.h
	$(cc) -c $(cppflag) SongDataBase.cpp

SortHelper.o: SortHelper.h SortHelper.cpp
	$(cc) -c $(cppflag) SortHelper.cpp

Parser.o: Parser.h Parser.cpp
	$(cc) -c $(cppflag) Parser.cpp

tar:
	tar cvf ex2.tar MIR.cpp Rankable.h Rankable.cpp Song.h Song.cpp \
					RankableSong.cpp RankableSong.h RankableLyricSong.cpp RankableLyricSong.h \
					RankableInstrumentalSong.h RankableInstrumentalSong.cpp \
					SongDataBase.h SongDataBase.cpp SongMatchingParams.h SongMatchingParams.cpp \
					SortHelper.h SortHelper.cpp Parser.h Parser.cpp README Makefile

clean:
	rm -f *.o MIR ex2.tar

.PHONY: all tar clean
