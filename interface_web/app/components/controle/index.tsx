
interface ControleProps {
    instrumentos: Record<string, string>;
    volume: number;
    setVolume: React.Dispatch<React.SetStateAction<number>>;
    instrumento: number;
    setInstrumento: React.Dispatch<React.SetStateAction<number>>;
    oitava: number;
    setOitava: React.Dispatch<React.SetStateAction<number>>;
    sendToESP: (v:number, i:number, o:number)=>void;
}

export default function Controle({ instrumentos, volume, setVolume, instrumento, setInstrumento, oitava, setOitava, sendToESP }: ControleProps) {

    const handleInstrumentoChange = (e: React.ChangeEvent<HTMLSelectElement>) => {
        const novoInstrumento = Number(e.target.value);
        setInstrumento(novoInstrumento);
        sendToESP(volume, novoInstrumento, oitava);
    };

    const alteraOitava = (direcao: number) => {
        let novaOitava = oitava + direcao;
        if (novaOitava < -3) novaOitava = -3;
        if (novaOitava > 4) novaOitava = 4;
        
        setOitava(novaOitava);
        sendToESP(volume, instrumento, novaOitava);
    };

    const handleVolumeChange = (e: React.ChangeEvent<HTMLInputElement>) => {
        const novoVolume = Number(e.target.value);

        setVolume(novoVolume);
        sendToESP(novoVolume, instrumento, oitava);
    };


    return (
        <div className="w-full bg-white/80 backdrop-blur-md p-8 rounded-xl border border-violet-300/50 flex flex-wrap items-center justify-between gap-12 shadow-sm">
        
            {/*Instrumento*/}
            <div className="flex flex-col gap-2 w-96">
                <span className="text-sm font-bold text-violet-700 uppercase">Instrumento</span>
                <select value={instrumento} onChange={handleInstrumentoChange} className="bg-violet-50 border border-violet-300 text-violet-900 rounded-lg p-2 font-medium focus:outline-none focus:ring-2 focus:ring-violet-500 h-[42px]">
                    {Object.entries(instrumentos).map(([id, nome]) => (
                        <option key={id} value={id}>
                        {id} - {nome}
                        </option>
                    ))}
                </select>
            </div>

            {/*Oitava*/}
            <div className="flex flex-col gap-2">
                <span className="text-sm font-bold text-violet-700 uppercase">Oitava</span>
                <div className="flex items-center bg-violet-50 border border-violet-300 rounded-lg overflow-hidden h-[42px]">
                    <button onClick={() => alteraOitava(-1)} className="px-3 h-full hover:bg-violet-200 text-violet-900 font-bold">-</button>
                    <span className="px-4 font-mono font-bold text-violet-900">{oitava}</span>
                    <button onClick={() => alteraOitava(1)} className="px-3 h-full hover:bg-violet-200 text-violet-900 font-bold">+</button>
                </div> 
            </div>

            {/*Volume*/}
            <div className="flex flex-col gap-2 flex-1 min-w-[150px]">
                <span className="text-sm font-bold text-violet-700 uppercase">Volume</span>
                <div className="flex items-center h-[42px]">
                    <input type="range" min="0" max="127" value={volume} onChange={handleVolumeChange} className="w-full h-2 bg-violet-100 accent-violet-600 rounded-lg appearance-none cursor-pointer" />
                </div>
            </div>

        </div>
    )
}