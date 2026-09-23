## System design of the Watch Party so far

### Tools
- Next.js   - Frontend
- C++       - Backend
- WebRTC    - Real time communication
- WebSocket - Persistent connection

```System
                         ┌──────────────────────┐
                         │      Web Client      │
                         │                      │
                         │  Create / Join Party │
                         │  Video Search        │
                         │  Chat                │
                         │  Voice Chat          │
                         └──────────┬───────────┘
                                    │
                    ┌───────────────┴───────────────┐
                    │                               │
                WebSocket                        WebRTC
            persistent connection              media / VC
                    │                               │
                    ▼                               ▼
        ┌──────────────────────┐        ┌──────────────────────┐
        │      C++ Server      │        │     WebRTC Peers     │
        │                      │        │                      │
        │  Party Management    │        │  Voice               │
        │  Join / Create       │        │  Video               │
        │  User Management     │        │  Screen Share*       │
        │  Chat                │        │                      │
        │  Video Sync          │        └──────────────────────┘
        │  Signaling           │
        └──────────┬───────────┘
                   │
                   │ Runtime State
                   ▼
        ┌─────────────────────────┐
        │      In-Memory State    │
        │                         │
        │  Party                  │
        │   ├── ID                │
        │   ├── Name              │
        │   ├── Private/Public    │
        │   ├── Password*         │
        │   ├── Host              │
        │   └── Users             │
        │                         │
        │  User                   │
        │   ├── Username          │
        │   └── Connection        │
        └─────────────────────────┘

        * Password only for private parties
        * Screen sharing planned for later
```


### Users
Users will have runtime scope, no datas of a user will be stored.

``` User flow
                 ┌──────────────┐
                 │     Home     │
                 └──────┬───────┘
                        │
             ┌──────────┴──────────┐
             ▼                     ▼
      ┌──────────────┐      ┌──────────────┐
      │    Create    │      │     Join     │
      └──────┬───────┘      └──────┬───────┘
             │                     │
       Party Name             Party ID
       Username               Username 
       Public/Private         Password*
             │                     │
             └──────────┬──────────┘
                        ▼
                ┌──────────────┐
                │     Party    │
                └──────┬───────┘
                       │
          ┌────────────┼────────────┐
          ▼            ▼            ▼
       ┌──────┐     ┌──────┐    ┌───────┐
       │  VC  │     │ Chat │    │ Video │
       └──────┘     └──────┘    └───────┘
```


### Party system
```Server
Server
│
├── WebSocket connections
│
├── Parties
│   ├── Party A
│   │   ├── User 1
│   │   ├── User 2
│   │   └── User 3
│   │
│   └── Party B
│       ├── User 4
│       └── User 5
│
└── Runtime state
```

### Party

A `Party` represents a single watch-party room.

Each party contains:

- A unique party ID and Password(If the Party is private)
- A set of connected client IDs

The `Party` class is responsible for managing clients within a party.

```text
Party
├── ID
├── Password
└── Clients
    ├── Client ID
    ├── Client ID
    └── Client ID
```
