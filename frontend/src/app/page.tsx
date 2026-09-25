"use client";

import { useRef, useState } from "react";

export default function Home() {
    const [name, setName] = useState("");
    const [roomId, setRoomId] = useState("");
    const [users, setUsers] = useState<string[]>([]);

    const ws = useRef<WebSocket | null>(null);

    const joinRoom = () => {
        const socket = new WebSocket("ws://localhost:8080/ws");

        ws.current = socket;

        socket.onopen = () => {
            console.log("Connected to server");

            socket.send(
                JSON.stringify({
                    type: "join",
                    name: name,
                    roomId: roomId
                })
            );
        };

        socket.onmessage = (event) => {
            const data = JSON.parse(event.data);

            console.log("Server:", data);

            if (data.type === "room_users") {
                setUsers(data.users);
            }
        };

        socket.onclose = () => {
            console.log("Disconnected");
        };
    };

    return (
        <div className="flex flex-col gap-4 p-10">

            <input
                placeholder="Your name"
                value={name}
                onChange={(e) => setName(e.target.value)}
                className="border p-2"
            />

            <input
                placeholder="Room ID"
                value={roomId}
                onChange={(e) => setRoomId(e.target.value)}
                className="border p-2"
            />

            <button
                onClick={joinRoom}
                className="border p-2"
            >
                Join Room
            </button>

            <h2>Users in room:</h2>

            {users.map((user) => (
                <p key={user}>
                    🟢 {user}
                </p>
            ))}

        </div>
    );
}