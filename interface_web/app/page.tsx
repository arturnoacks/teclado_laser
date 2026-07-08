"use client";

import { useEffect, useRef, useState } from "react";

import Header from "./components/header";
import Teclado from "./components/teclado";
import Controle from "./components/controle";

import instrumentos from "@/instrumentos.json"

export default function Home() {

    const ws = useRef<WebSocket | null>(null);

    const [volume, setVolume] = useState(63);
    const [instrumento, setInstrumento] = useState(0);
    const [oitava, setOitava] = useState(0);

    const [notasAtivas, setNotasAtivas] = useState<number[]>([]);

    useEffect(() => {
        const ESP_IP = "10.187.201.1"; 
        const socket = new WebSocket(`ws://${ESP_IP}:81`);

        ws.current = socket;

        socket.onmessage = (event) => {
            const data = JSON.parse(event.data);

            if (data.v !== undefined) {
                setVolume(data.v);
            }

            if (data.i !== undefined) {
                setInstrumento(data.i);
            }

            if (data.o !== undefined) {
                setOitava(data.o);
            }

            if (data.n !== undefined && data.s !== undefined) {
                setNotasAtivas(prev => {
                    if (data.s == 1)
                        return prev.includes(data.n) ? prev : [...prev, data.n];
                    return prev.filter(n => n != data.n);
                });
            }
        };

        return () => socket.close();
    }, []);

    const sendToESP = (v:number,i:number,o:number)=>{
        if(ws.current && ws.current.readyState === WebSocket.OPEN){
            ws.current.send(JSON.stringify({v,i,o}));

        }
    };


    return (
        <div className="h-screen w-full flex flex-col items-center bg-violet-200 pt-16">
            
            <Header/>

            <div className="mt-32">
            <Controle instrumentos={instrumentos} volume={volume} setVolume={setVolume} instrumento={instrumento} setInstrumento={setInstrumento} 
            oitava={oitava} setOitava={setOitava} sendToESP={sendToESP}/>
            </div>
            
            <div className="mt-16 transform scale-80 shadow-2xl">
            <Teclado notasAtivas={notasAtivas}/>
            </div>
            
        </div>
    );
}
