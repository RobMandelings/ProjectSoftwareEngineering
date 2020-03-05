//
// Created by Rob Mandelings on 5/03/2020.
//

#include "Track.h"

Track::Track(int trackIndex, TrackNode* firstNode) :
        m_trackIndex(trackIndex),
        m_firstNode(firstNode) {}

int Track::getTrackIndex() const {
    return m_trackIndex;
}

TrackNode* Track::getFirstNode() const {
    return m_firstNode;
}