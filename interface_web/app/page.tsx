import Header from "./components/header";
import Teclado from "./components/teclado";
import Controle from "./components/controle";

import instrumentos from "@/instrumentos.json"

export default function Home() {


  return (
    <div className="h-screen w-full flex flex-col items-center bg-violet-200 pt-16">
      
      <Header/>

      <div className="mt-32">
        <Controle instrumentos={instrumentos}/>
      </div>
      
      <div className="mt-16 transform scale-80 shadow-2xl">
        <Teclado/>
      </div>
      
    </div>
  );
}
