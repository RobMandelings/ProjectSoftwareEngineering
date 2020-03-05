//
// Created by Rob Mandelings on 5/03/2020.
//

#pragma once


#include "TrackNode.h"

class Track {

private:

    int m_trackIndex;
    TrackNode* m_firstNode;

public:

    Track(int trackIndex, TrackNode* firstNode);

    int getTrackIndex() const;

    TrackNode* getFirstNode() const;

};