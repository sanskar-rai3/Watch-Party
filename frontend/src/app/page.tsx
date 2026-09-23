"use client"

import axios from "axios";
import { useEffect } from "react";

export default async function Home() {
  const ws = new WebSocket("ws://localhost:8080/ws")
  useEffect(() => {

    ws.onopen = () => {
      console.log("Connection established");
      ws.send("Calling from Next js")
      
    }

    ws.onmessage = (event) => {
      console.log("From the server: ", event.data);

    }

    ws.onerror = (error) => {
      console.error("WebSocket error:", error);
    };
    ws.onclose = (event) => {
      console.log("Connection closed");
      console.log("Code:", event.code);
      console.log("Reason:", event.reason);
    };

    
  })



  return (
    <div className="flex items-center justify-center gap-10">
      <button>Join room</button>
      <button>Create room</button>
    </div>
  );
}
