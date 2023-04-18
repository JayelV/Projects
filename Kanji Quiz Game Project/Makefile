# Makefile for Kanji Quiz classes

all: run.py KanjiServer KanjiClient KanjiDriver1 QuizDriver1 ChapterDriver

all: run.py libDriver KanjiServer KanjiClient KanjiDriver1 KQuizDriver ChapterClient ChapterServer ChapterDriver

all: run.py libDriver KanjiServer KanjiClient KanjiDriver1 KQuizDriver ChapterClient ChapterServer ChapterDriver a.out
		./libDriver |& diff - libDriver.out
		./KanjiDriver1 |& diff - KanjiDriver1.out
		./ChapterDriver |& diff - ChapterDriver.out

run.py:
	cp /usr/local/cs/cs251/lab10/$@ .

react.%:
	cp /usr/local/cs/cs251/$@ react.$*

ChapterServer.o:  ChapterServer.cpp Comm.h Chapter.h lib.h ../react.h
	g++ -Wall -c ChapterServer.cpp -lcurl	

ChapterServer: ChapterServer.o Chapter.o lib.o ../react.o
	g++ -Wall -o ChapterServer ChapterServer.o Chapter.o Kanji.o lib.o ../react.o -lcurl     

ChapterClient.o:  ChapterClient.cpp Comm.h ../react.h 
	g++ -Wall -c ChapterClient.cpp -lcurl    

ChapterClient: ChapterClient.o react.h ../react.o
	g++ -Wall -o ChapterClient ChapterClient.cpp ../react.o -lcurl

Chapter.o: Chapter.cpp Chapter.h lib.o ../react.h
	g++    -Wall -c Chapter.cpp

ChapterDriver.o:    ChapterDriver.cpp Chapter.h lib.o ../react.h
	g++    -Wall -c ChapterDriver.cpp

ChapterDriver: ChapterDriver.o Chapter.o Kanji.o lib.o ../react.o
	g++    -Wall -o ChapterDriver ChapterDriver.o Chapter.o Kanji.o lib.o ../react.o -lcurl

lib.o:  lib.cpp lib.h ../react.h
	g++ -Wall -c lib.cpp

libDriver.o:  libDriver.cpp lib.h ../react.h
	g++ -Wall -c libDriver.cpp

libDriver:  libDriver.o KQuiz.o Chapter.o Kanji.o lib.o ../react.o
	g++ -o libDriver libDriver.o KQuiz.o Chapter.o Kanji.o lib.o ../react.o -lcurl


KanjiServer.o:  KanjiServer.cpp Comm.h Kanji.h lib.h ../react.h
	g++ -Wall -c KanjiServer.cpp -lcurl    

KanjiServer: KanjiServer.o Kanji.o lib.o ../react.o
	g++ -Wall -o KanjiServer KanjiServer.o Kanji.o Chapter.o lib.o ../react.o -lcurl     

KanjiClient.o:  KanjiClient.cpp Comm.h ../react.h 
	g++ -Wall -c KanjiClient.cpp -lcurl    

KanjiClient: KanjiClient.o react.h ../react.o
	g++ -Wall -o KanjiClient KanjiClient.cpp ../react.o -lcurl


Kanji.o: Kanji.cpp Kanji.h lib.o ../react.h
	g++    -Wall -c Kanji.cpp

KanjiDriver1.o:    KanjiDriver1.cpp Kanji.h lib.o ../react.h
	g++    -Wall -c KanjiDriver1.cpp

KanjiDriver1: KanjiDriver1.o Kanji.o Chapter.o lib.o ../react.o
	g++    -Wall -o KanjiDriver1 KanjiDriver1.o Kanji.o Chapter.o lib.o ../react.o -lcurl


ChapterServer.o:  ChapterServer.cpp Comm.h Chapter.h lib.h ../react.h
	g++ -Wall -c ChapterServer.cpp -lcurl    

ChapterServer: ChapterServer.o Chapter.o lib.o ../react.o
	g++ -Wall -o ChapterServer ChapterServer.o Chapter.o Kanji.o lib.o ../react.o -lcurl     

ChapterClient.o:  ChapterClient.cpp Comm.h ../react.h 
	g++ -Wall -c ChapterClient.cpp -lcurl    

ChapterClient: ChapterClient.o react.h ../react.o
	g++ -Wall -o ChapterClient ChapterClient.cpp ../react.o -lcurl

Chapter.o: Chapter.cpp Chapter.h lib.o ../react.h
	g++    -Wall -c Chapter.cpp

ChapterDriver.o:    ChapterDriver.cpp Chapter.h lib.o ../react.h
	g++    -Wall -c ChapterDriver.cpp

ChapterDriver: ChapterDriver.o Chapter.o Kanji.o lib.o ../react.o
	g++    -Wall -o ChapterDriver ChapterDriver.o Chapter.o Kanji.o lib.o ../react.o -lcurl


KQuiz.o:	KQuiz.cpp KQuiz.h lib.o ../react.h
	g++    -Wall -c KQuiz.cpp

KQuizDriver.o: KQuizDriver.cpp KQuiz.h lib.o ../react.h
	g++    -Wall -c KQuizDriver.cpp

KQuizDriver: KQuizDriver.o KQuiz.o Chapter.o Kanji.o lib.o ../react.o
	g++    -Wall -o KQuizDriver KQuizDriver.o KQuiz.o Chapter.o Kanji.o lib.o ../react.o -lcurl


KanjiQuizApp.o: KanjiQuizApp.cpp ../react.h
	g++    -Wall -c KanjiQuizApp.cpp -lcurl

a.out: KanjiQuizApp.o KQuiz.o Chapter.o Kanji.o lib.o ../react.o
	g++    -Wall -o a.out KanjiQuizApp.o KQuiz.o Chapter.o Kanji.o lib.o ../react.o -lcurl