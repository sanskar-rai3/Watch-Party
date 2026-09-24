"use client"

import axios from "axios";
import { useEffect } from "react";

export default function Home() {
  // useEffect(() => {

  //   const ws = new WebSocket("ws://localhost:8080/ws")
  //   ws.onopen = () => {
  //     console.log("Connection established");
  //     ws.send("Calling from Next js")

  //   }

  //   ws.onmessage = (event) => {
  //     console.log("From the server: ", event.data);

  //   }

  //   ws.onerror = (error) => {
  //     console.error("WebSocket error:", error);
  //   };
  //   ws.onclose = (event) => {
  //     console.log("Connection closed");
  //     console.log("Code:", event.code);
  //     console.log("Reason:", event.reason);
  //   };


  // })

  const createParty = async () => {
    try {
      const partyData = {
        host: "Ayush",
        partyName: "My Watch Party",
        maxUsers: 10
      };

      const res = await axios.post(
        "http://localhost:8080/api/party/create",
        partyData,
        {
          headers: {
            "Content-Type": "application/json"
          }
        }
      );

      console.log("Server response:", res.data);

    } catch (error) {
      console.error(error);
    }
  };


  useEffect(() => {
    createParty();
  }, [])


  return (
    <div className="flex items-center justify-center gap-10">
      <button>Join room</button>
      <button>Create room</button>
    </div>
  );
}
