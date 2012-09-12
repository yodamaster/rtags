#ifndef MAKEFILEPARSER_H
#define MAKEFILEPARSER_H

#include "Path.h"
#include "GccArguments.h"
#include <List.h>
#include <Map.h>
#include <SignalSlot.h>

class Connection;
class Process;

class MakefileParser
{
public:
    MakefileParser(const List<ByteArray> &extraFlags, Connection *conn);
    ~MakefileParser();

    void run(const Path &makefile, const List<ByteArray> &args);
    void stop();
    bool isDone() const;
    List<ByteArray> extraFlags() const { return mExtraFlags; }
    Path makefile() const { return mMakefile; }
    Connection *connection() const { return mConnection; }
    signalslot::Signal1<MakefileParser*> &done() { return mDone; }
    signalslot::Signal2<const GccArguments &, MakefileParser*> &fileReady() { return mFileReady; }
    int sourceCount() const { return mSourceCount; }
private:
    void processMakeOutput();
    void processMakeError();
    void processMakeLine(const ByteArray &line);
    void onDone();

    Process *mProc;
    ByteArray mData;
    const List<ByteArray> mExtraFlags;
    int mSourceCount;
    Path mMakefile;
    Connection *mConnection;
    signalslot::Signal1<MakefileParser*> mDone;
    signalslot::Signal2<const GccArguments &, MakefileParser*> mFileReady;
    Map<Path, List<ByteArray> > mPendingFiles;
    Path mCurrentPath;
};

#endif // MAKEFILEPARSER_H
