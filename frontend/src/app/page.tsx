"use client";

import { useRef, useState } from "react";
import type { ChangeEvent } from "react";

interface FormData {
  name: string;
  roomId: string;
}

interface ServerMessage {
  type: string;
  message?: string;
  roomId: string;
}

export default function Home() {
  const [data, setData] = useState<FormData>({
    name: "",
    roomId: ""
  });

  const ws = useRef<WebSocket | null>(null);

  const handleChange = (e: ChangeEvent<HTMLInputElement>) => {
    const { name, value } = e.target;

    setData((prev) => ({
      ...prev,
      [name]: value
    }));
  };

  const joinParty = () => {
    if (!data.name || !data.roomId) {
      console.log("Name and room ID are required");
      return;
    }

    // Create WebSocket connection
    const socket = new WebSocket(
      "ws://localhost:8080/ws"
    );

    ws.current = socket;

    socket.onopen = () => {
      console.log("WebSocket connected");

      // Send join information to C++ server
      socket.send(
        JSON.stringify({
          type: "join",
          name: data.name,
          roomId: data.roomId
        })
      );
    };

    socket.onmessage = (event) => {
      const message: ServerMessage =
        JSON.parse(event.data);

      console.log("Server:", message);
    };

    socket.onerror = (error) => {
      console.error("WebSocket error:", error);
    };

    socket.onclose = () => {
      console.log("WebSocket disconnected");
    };
  };

  return (
    <div className="flex flex-col gap-4">
      <input
        type="text"
        name="name"
        value={data.name}
        onChange={handleChange}
        placeholder="Enter your name"
      />

      <input
        type="text"
        name="roomId"
        value={data.roomId}
        onChange={handleChange}
        placeholder="Enter room ID"
      />

      <button onClick={joinParty}>
        Join Party
      </button>
    </div>
  );
}
