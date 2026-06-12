
interface ControleProps {
    instrumentos: Record<string, string>;
}

export default function Controle({ instrumentos }: ControleProps) {

    return (
        <div className="w-full bg-white/80 backdrop-blur-md p-8 rounded-xl border border-violet-300/50 flex flex-wrap items-center justify-between gap-12 shadow-sm">
        
            {/*Instrumento*/}
            <div className="flex flex-col gap-2 w-96">
                <span className="text-sm font-bold text-violet-700 uppercase">Instrumento</span>
                <select className="bg-violet-50 border border-violet-300 text-violet-900 rounded-lg p-2 font-medium focus:outline-none focus:ring-2 focus:ring-violet-500 h-[42px]">
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
                    <button className="px-3 h-full hover:bg-violet-200 text-violet-900 font-bold">-</button>
                    <span className="px-4 font-mono font-bold text-violet-900">0</span>
                    <button className="px-3 h-full hover:bg-violet-200 text-violet-900 font-bold">+</button>
                </div> 
            </div>

            {/*Volume*/}
            <div className="flex flex-col gap-2 flex-1 min-w-[150px]">
                <span className="text-sm font-bold text-violet-700 uppercase">Volume</span>
                <div className="flex items-center h-[42px]">
                    <input type="range" className="w-full h-2 bg-violet-100 accent-violet-600 rounded-lg appearance-none cursor-pointer" />
                </div>
            </div>

            {/*Pitch*/}
            <div className="flex flex-col gap-2 min-w-[150px]">
                <span className="text-sm font-bold text-violet-700 uppercase">Pitch</span>
                <div className="flex items-center h-[42px]">
                    <input type="range" min="-100" max="100" defaultValue="0" className="w-full h-2 bg-violet-100 accent-violet-600 rounded-lg appearance-none cursor-pointer" />
                </div>
            </div>

        </div>
    )
}