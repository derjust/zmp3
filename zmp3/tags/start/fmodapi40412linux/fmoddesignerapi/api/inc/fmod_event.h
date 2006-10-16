/*
    fmod_event.h - Data-driven event classes
    Copyright (c), Firelight Technologies Pty, Ltd. 2004-2006.
*/

#ifndef __FMOD_EVENT_H__
#define __FMOD_EVENT_H__

#ifndef _FMOD_HPP
#include "fmod.hpp"
#endif

/*
    FMOD EventSystem version number.  Check this against FMOD::EventSystem::getVersion.
    0xaaaabbcc -> aaaa = major version number.  bb = minor version number.  cc = development version number.
*/

#define FMOD_EVENT_VERSION 0x00010410

/*
    FMOD event types
*/

typedef unsigned int EVENT_MODE;
typedef unsigned int EVENT_STATE;

namespace FMOD
{
    class EventSystem;
    class EventCategory;
    class EventGroup;
    class Event;
    class EventParameter;


    /*
    [DEFINE]
    [
        [NAME] 
        EVENT_MODE

        [DESCRIPTION]   
        Event data loading bitfields. Bitwise OR them together for controlling how event data is loaded.

        [REMARKS]

        [PLATFORMS]
        Win32, Win64, Linux, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

        [SEE_ALSO]
        EventGroup::loadEventData
        EventGroup::getEvent
        EventGroup::getEventByIndex
    ]
    */
    #define EVENT_DEFAULT               0x00000000  /* EVENT_DEFAULT specifies default loading behaviour i.e. event data for the whole group is NOT cached and the function that initiated the loading process will block until loading is complete. */
    #define EVENT_NONBLOCKING           0x00000001  /* For loading event data asynchronously. FMOD will use a thread to load the data.  Use Event::getState to find out when loading is complete. */
    #define EVENT_ERROR_ON_DISKACCESS   0x00000002  /* For EventGroup::getEvent / EventGroup::getEventByIndex.  If EventGroup::loadEventData has accidently been forgotten this flag will return an FMOD_ERR_FILE_UNWANTED if the getEvent function tries to load data. */
    #define EVENT_INFOONLY              0x00000004  /* For EventGroup::getEvent / EventGroup::getEventByIndex.  Don't allocate instances or load data, just get a handle to allow user to get information from the event. */
    /* [DEFINE_END] */


    /*
    [DEFINE]
    [
        [NAME] 
        EVENT_STATE

        [DESCRIPTION]   
        These values describe what state an event is in.

        [REMARKS]    
        The flags below can be combined to set multiple states at once.  Use bitwise AND operations to test for these.
        An example of a combined flag set would be EVENT_STATE_READY | EVENT_STATE_PLAYING.

        [PLATFORMS]
        Win32, Win64, Linux, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

        [SEE_ALSO]
        Event::getState
        EVENT_MODE
    ]
    */
    #define EVENT_STATE_READY           0x00000001  /* Event is ready to play. */
    #define EVENT_STATE_LOADING         0x00000002  /* Loading in progress. */
    #define EVENT_STATE_ERROR           0x00000004  /* Failed to open - file not found, out of memory etc.  See return value of Event::getState for what happened. */
    #define EVENT_STATE_PLAYING         0x00000008  /* Event has been started.  This will still be true even if the're are no sound active.  Event::stop must be called or the event must stop itself using a 'one shot and stop event' parameter mode. */
    #define EVENT_STATE_CHANNELSACTIVE  0x00000010  /* Event has active voices.  Use this if you want to detect if sounds are playing in the event or not. */
    /* [DEFINE_END] */


    /*
    [ENUM]
    [
	    [DESCRIPTION]
        Property indices for Event::getPropertyByIndex.
        
	    [REMARKS]        

        [PLATFORMS]
        Win32, Win64, Linux, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

	    [SEE_ALSO]
        Event::getPropertyByIndex
    ]
    */
    typedef enum
    {
        EVENTPROPERTY_NAME = 0,                 /* Type : char *    - Name of event. */
        EVENTPROPERTY_VOLUME,                   /* Type : float     - Relative volume of event. */
        EVENTPROPERTY_PITCH,                    /* Type : float     - Relative pitch of event. */
        EVENTPROPERTY_PRIORITY,                 /* Type : int       - Playback priority of event. */
        EVENTPROPERTY_MAX_PLAYBACKS,            /* Type : int       - Maximum simultaneous playbacks of event. */
        EVENTPROPERTY_MAX_PLAYBACKS_BEHAVIOR,   /* Type : int       - 0 = steal next, 1 = steal oldest, 2 = steal newest, 3 = steal quietest, 4 = just fail. */
        EVENTPROPERTY_MODE,                     /* Type : FMOD_MODE - Either FMOD_3D or FMOD_2D. */
        EVENTPROPERTY_3D_ROLLOFF,               /* Type : FMOD_MODE - Either FMOD_3D_LOGROLLOFF, FMOD_3D_LINEARROLLOFF, or none for custom rolloff.. */
        EVENTPROPERTY_3D_MINDISTANCE,           /* Type : float     - Minimum 3d distance of event. */
        EVENTPROPERTY_3D_MAXDISTANCE,           /* Type : float     - Maximum 3d distance of event.  Means different things depending on EVENTPROPERTY_3D_ROLLOFF. */
        EVENTPROPERTY_3D_POSITION,              /* Type : FMOD_MODE - Either FMOD_3D_HEADRELATIVE or FMOD_3D_WORLDRELATIVE. */
        EVENTPROPERTY_3D_CONEINSIDEANGLE,       /* Type : float     - Event cone inside angle.  0 to 360. */
        EVENTPROPERTY_3D_CONEOUTSIDEANGLE,      /* Type : float     - Event cone outside angle.  0 to 360. */
        EVENTPROPERTY_3D_CONEOUTSIDEVOLUME,     /* Type : float     - Event cone outside volume.  0 to 1.0. */
        EVENTPROPERTY_3D_DOPPLERSCALE,          /* Type : float     - Doppler scale where 0 = no doppler, 1.0 = normal doppler, 2.0 = double doppler etc. */
        EVENTPROPERTY_3D_REVERBLEVEL,           /* Type : float     - Reverb mix for this event where 0 = full reverb, -60 = no reverb. */
        EVENTPROPERTY_SPEAKER_L,                /* Type : float     - 2D event volume for front left speaker. */
        EVENTPROPERTY_SPEAKER_C,                /* Type : float     - 2D event volume for front left speaker. */
        EVENTPROPERTY_SPEAKER_R,                /* Type : float     - 2D event volume for front left speaker. */
        EVENTPROPERTY_SPEAKER_LS,               /* Type : float     - 2D event volume for front left speaker. */
        EVENTPROPERTY_SPEAKER_RS,               /* Type : float     - 2D event volume for front left speaker. */
        EVENTPROPERTY_SPEAKER_LR,               /* Type : float     - 2D event volume for front left speaker. */
        EVENTPROPERTY_SPEAKER_RR,               /* Type : float     - 2D event volume for front left speaker. */
        EVENTPROPERTY_SPEAKER_LFE,              /* Type : float     - 2D event volume for front left speaker. */
        EVENTPROPERTY_MUSIC,                    /* Type : int       - For Xbox360.  Signifies that this event is music, so that the dashboard can override it if required.  0 = false, 1 = true. */
        EVENTPROPERTY_USER_BASE                 /* User created events start from here onwards. */
    } EVENT_PROPERTY;


    /*
    [ENUM]
    [
	    [DESCRIPTION]
        Flags to pass to EventGroup::loadEventData to determine what to load at the time of calling.
        
	    [REMARKS]

        [PLATFORMS]
        Win32, Win64, Linux, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

	    [SEE_ALSO]
        EventGroup::loadEventData
    ]
    */
    typedef enum
    {
        EVENT_RESOURCE_STREAMS_AND_SAMPLES, /* Open all streams and load all banks into memory, under this group (recursive) */
        EVENT_RESOURCE_STREAMS,             /* Open all streams under this group (recursive).  No samples are loaded. */
        EVENT_RESOURCE_SAMPLES              /* Load all banks into memory, under this group (recursive).  No streams are opened. */
    } EVENT_RESOURCE;


    /*
    [ENUM]
    [
        [DESCRIPTION]   
        These callback types are used with EVENT_CALLBACK.

        [REMARKS]
        <b>Note!</b>  Currently the user must call EventSystem::update for these callbacks to trigger!
        <br>
        An EVENT_CALLBACKTYPE_SYNCPOINT callback is generated from 'markers' embedded in .wav files.
        These can be created by placing 'markers' in the original source wavs using a tool such as Sound Forge or Cooledit.<br>
        The wavs are then compiled into .FSB files when compiling the audio data using the FMOD designer tool.<br>
        Callbacks will be automatically generated at the correct place in the timeline when these markers are encountered
        which makes it useful for synchronization, lip syncing etc.<br>
        <br>
        An EVENT_CALLBACKTYPE_SOUNDDEF_START callback is generated each time a sound definition is played in an event.<br>
        This happens every time a sound definition starts due to the event parameter entering the region specified in the 
        layer created by the sound designer..<br>
        This also happens when sounds are randomly respawned using the random respawn feature in the sound definition 
        properties in FMOD designer.<br>
        <br>
        An EVENT_CALLBACKTYPE_SOUNDDEF_END callback is generated when a one-shot sound definition inside an event ends, 
        or when a looping sound definition stops due to the event parameter leaving the region specified in the layer created 
        by the sound designer.<br>
        <br>
        An EVENT_CALLBACKTYPE_NET_MODIFIED callback is generated when someone has connected to your running application with 
        FMOD Designer and changed a property within this event, for example volume or pitch.<br>

        [PLATFORMS]
        Win32, Win64, Linux, Macintosh, Xbox, Xbox360, PlayStation 2, GameCube, PlayStation Portable, PlayStation 3

        [SEE_ALSO]      
        Event::setCallback
        EVENT_CALLBACK
        EventSystem::update
    ]
    */
    typedef enum
    {
        EVENT_CALLBACKTYPE_SYNCPOINT,              /* Called when a syncpoint is encountered.  Can be from wav file markers. */
        EVENT_CALLBACKTYPE_SOUNDDEF_START,         /* Called when a sound definition inside an event is triggered. */
        EVENT_CALLBACKTYPE_SOUNDDEF_END,           /* Called when a sound definition inside an event ends or is stopped. */
        EVENT_CALLBACKTYPE_STOLEN,                 /* Called when an event runs out of instances and re-uses an existing event. */
        EVENT_CALLBACKTYPE_EVENTFINISHED,          /* Called when a non looping event parameter causes an event stop. */
        EVENT_CALLBACKTYPE_NET_MODIFIED            /* Called when a property of the event has been modified by a network-connected host. */
    } EVENT_CALLBACKTYPE;

    typedef FMOD_RESULT (F_CALLBACK *EVENT_CALLBACK)(Event *event, EVENT_CALLBACKTYPE type, void *param1, void *param2, void *userdata);

    /*
        FMOD EventSystem API
    */

    FMOD_RESULT F_API EventSystem_Create(EventSystem **eventsystem);    /* Call this first to create an EventSystem object. */

    class EventSystem
    {
        public :

        virtual FMOD_RESULT F_API init               (int maxchannels, FMOD_INITFLAGS flags, void *extradriverdata) = 0;
        virtual FMOD_RESULT F_API release            () = 0;
        virtual FMOD_RESULT F_API update             () = 0;
        virtual FMOD_RESULT F_API setMediaPath       (const char *path) = 0;
        virtual FMOD_RESULT F_API setPluginPath      (const char *path) = 0;
        virtual FMOD_RESULT F_API getVersion         (unsigned int *version) = 0;

        virtual FMOD_RESULT F_API load               (const char *filename, const char *encryptionkey) = 0;
        virtual FMOD_RESULT F_API unload             () = 0;

        virtual FMOD_RESULT F_API getGroup           (const char *name, bool cacheevents, EventGroup **group) = 0;
        virtual FMOD_RESULT F_API getGroupByIndex    (int index,        bool cacheevents, EventGroup **group) = 0;
        virtual FMOD_RESULT F_API getNumGroups       (int *numgroups) = 0;
        virtual FMOD_RESULT F_API getCategory        (const char *name, EventCategory **category) = 0;
        virtual FMOD_RESULT F_API getCategoryByIndex (int index,        EventCategory **category) = 0;
        virtual FMOD_RESULT F_API getNumCategories   (int *numcategories) = 0;

        virtual FMOD_RESULT F_API getSystemObject    (System **system) = 0;

        virtual FMOD_RESULT F_API set3DNumListeners  (int numlisteners) = 0;
        virtual FMOD_RESULT F_API get3DNumListeners  (int *numlisteners) = 0;
        virtual FMOD_RESULT F_API set3DListenerAttributes(int listener, const FMOD_VECTOR *pos, const FMOD_VECTOR *vel, const FMOD_VECTOR *forward, const FMOD_VECTOR *up) = 0;
        virtual FMOD_RESULT F_API get3DListenerAttributes(int listener, FMOD_VECTOR *pos, FMOD_VECTOR *vel, FMOD_VECTOR *forward, FMOD_VECTOR *up) = 0;
    };


    class EventGroup
    {
        public :

        virtual FMOD_RESULT F_API loadEventData      (EVENT_RESOURCE resource, EVENT_MODE mode = EVENT_DEFAULT) = 0;
        virtual FMOD_RESULT F_API freeEventData      () = 0;
        virtual FMOD_RESULT F_API getInfo            (int *index, char **name) = 0;
        virtual FMOD_RESULT F_API getGroup           (const char *name, bool cacheevents, EventGroup **group) = 0;
        virtual FMOD_RESULT F_API getGroupByIndex    (int index,        bool cacheevents, EventGroup **group) = 0;
        virtual FMOD_RESULT F_API getNumGroups       (int *numgroups) = 0;
        virtual FMOD_RESULT F_API getEvent           (const char *name, EVENT_MODE mode, Event **event) = 0;
        virtual FMOD_RESULT F_API getEventByIndex    (int index,        EVENT_MODE mode, Event **event) = 0;
        virtual FMOD_RESULT F_API getNumEvents       (int *numevents) = 0;
    };


    class EventCategory
    {
        public :

        virtual FMOD_RESULT F_API getInfo            (int *index, char **name) = 0;
        virtual FMOD_RESULT F_API getCategory        (const char *name, EventCategory **category) = 0;
        virtual FMOD_RESULT F_API getCategoryByIndex (int index,        EventCategory **category) = 0;
        virtual FMOD_RESULT F_API getNumCategories   (int *numcategories) = 0;
        virtual FMOD_RESULT F_API getParameter       (const char *name, EventParameter **parameter) = 0;
        virtual FMOD_RESULT F_API getParameterByIndex(int index,        EventParameter **parameter) = 0;
        virtual FMOD_RESULT F_API getNumParameters   (int *numparameters) = 0;
        virtual FMOD_RESULT F_API getVolume          (float *volume) = 0;
        virtual FMOD_RESULT F_API setVolume          (float volume) = 0;
        virtual FMOD_RESULT F_API getPitch           (float *pitch) = 0;
        virtual FMOD_RESULT F_API setPitch           (float pitch) = 0;
        virtual FMOD_RESULT F_API getPaused          (bool *paused) = 0;
        virtual FMOD_RESULT F_API setPaused          (bool paused) = 0;
        virtual FMOD_RESULT F_API getMute            (bool *mute) = 0;
        virtual FMOD_RESULT F_API setMute            (bool mute) = 0;
        virtual FMOD_RESULT F_API getChannelGroup    (ChannelGroup **channelgroup) = 0;
    };


    class Event
    {
        public :

        FMOD_RESULT F_API start                      ();
        FMOD_RESULT F_API stop                       ();
        FMOD_RESULT F_API getInfo                    (int *index, char **name, char ***soundbanknames);
        FMOD_RESULT F_API getParameter               (const char *name, EventParameter **parameter);
        FMOD_RESULT F_API getParameterByIndex        (int index, EventParameter **parameter);
        FMOD_RESULT F_API getNumParameters           (int *numparameters);
        FMOD_RESULT F_API getProperty                (const char *propertyname, void *value);
        FMOD_RESULT F_API getPropertyByIndex         (int propertyindex, void *value);
        FMOD_RESULT F_API getNumProperties           (int *numproperties);
        FMOD_RESULT F_API getCategoryByIndex         (int categoryindex, EventCategory **category);
        FMOD_RESULT F_API getNumCategories           (int *numcategories);
        FMOD_RESULT F_API setVolume                  (float volume);
        FMOD_RESULT F_API getVolume                  (float *volume);
        FMOD_RESULT F_API setPitch                   (float pitch);
        FMOD_RESULT F_API getPitch                   (float *pitch);
        FMOD_RESULT F_API setPaused                  (bool paused);
        FMOD_RESULT F_API getPaused                  (bool *paused);
        FMOD_RESULT F_API setMute                    (bool mute);
        FMOD_RESULT F_API getMute                    (bool *mute);
        FMOD_RESULT F_API set3DAttributes            (const FMOD_VECTOR *position, const FMOD_VECTOR *velocity, const FMOD_VECTOR *orientation = 0);
        FMOD_RESULT F_API get3DAttributes            (FMOD_VECTOR *position, FMOD_VECTOR *velocity, FMOD_VECTOR *orientation = 0);
        FMOD_RESULT F_API set3DOcclusion             (float directocclusion, float reverbocclusion);
        FMOD_RESULT F_API get3DOcclusion             (float *directocclusion, float *reverbocclusion);
        FMOD_RESULT F_API setReverbProperties        (const FMOD_REVERB_CHANNELPROPERTIES *prop);
        FMOD_RESULT F_API getReverbProperties        (FMOD_REVERB_CHANNELPROPERTIES *prop);
        FMOD_RESULT F_API getState                   (EVENT_STATE *state);
        FMOD_RESULT F_API setCallback                (EVENT_CALLBACK callback, void *userdata);
        FMOD_RESULT F_API getParentGroup             (EventGroup **group);
    };


    class EventParameter
    {
        public :

        FMOD_RESULT F_API getInfo                    (int *index, char **name);
        FMOD_RESULT F_API getRange                   (float *rangemin, float *rangemax);
        FMOD_RESULT F_API setValue                   (float value);
        FMOD_RESULT F_API getValue                   (float *value);
        FMOD_RESULT F_API setVelocity                (float value);
        FMOD_RESULT F_API getVelocity                (float *value);
        FMOD_RESULT F_API keyOff                     ();
    };
}


#endif
