
interface TecladoProps{
    notasAtivas: number[];
}

export default function Teclado({ notasAtivas }:TecladoProps) {

    const teclas = [
        // Oitava 1
        { tipo: 'branca', d: "M115 521.67V301.003H87V1.00299H1V521.67H115Z" },     // Dó
        { tipo: 'preta',  d: "M142.979 301.003V1.00323H86.9791V301.003H142.979Z" }, // Dó#
        { tipo: 'branca', d: "M229 521.67V301.015H201V1.00006H143V301.015H115V521.67H229Z" }, // Ré
        { tipo: 'preta',  d: "M257 301V1.00006H201V301H257Z" },                     // Ré#
        { tipo: 'branca', d: "M343 521.67H229V301.003H257V1.00299H343V521.67Z" },   // Mi
        { tipo: 'branca', d: "M457 521.67V301.003H429V1.00299H343V521.67H457Z" },   // Fá
        { tipo: 'preta',  d: "M484.979 301.003V1.00323H428.979V301.003H484.979Z" }, // Fá#
        { tipo: 'branca', d: "M571 521.67V301.015H543V1.00006H485V301.015H457V521.67H571Z" }, // Sol
        { tipo: 'preta',  d: "M599 301V1.00006H543V301H599Z" },                     // Sol#
        { tipo: 'branca', d: "M685 521.67V301.015H657V1.00006H599V301.015H571V521.67H685Z" }, // Lá
        { tipo: 'preta',  d: "M713 301V1.00006H657V301H713Z" },                     // Lá#
        { tipo: 'branca', d: "M799 521.67H685V301.003H713V1.00299H799V521.67Z" },   // Si
        
        // Oitava 2
        { tipo: 'branca', d: "M913 521.67V301.003H885V1.00299H799V521.67H913Z" },   // Dó
        { tipo: 'preta',  d: "M940.979 301.003V1.00323H884.979V301.003H940.979Z" }, // Dó#
        { tipo: 'branca', d: "M1027 521.67V301.015H999V1.00006H941V301.015H913V521.67H1027Z" },// Ré
        { tipo: 'preta',  d: "M1055 301V1.00006H999V301H1055Z" },                   // Ré#
        { tipo: 'branca', d: "M1141 521.67H1027V301.003H1055V1.00299H1141V521.67Z" },// Mi
        { tipo: 'branca', d: "M1255 521.67V301.003H1227V1.00299H1141V521.67H1255Z" },// Fá
        { tipo: 'preta',  d: "M1282.98 301.003V1.00323H1226.98V301.003H1282.98Z" }, // Fá#
        { tipo: 'branca', d: "M1369 521.67V301.015H1341V1.00006H1283V301.015H1255V521.67H1369Z" }, // Sol
        { tipo: 'preta',  d: "M1397 301V1.00006H1341V301H1397Z" },                  // Sol#
        { tipo: 'branca', d: "M1483 521.67V301.015H1455V1.00006H1397V301.015H1369V521.67H1483Z" }, // Lá
        { tipo: 'preta',  d: "M1511 301V1.00006H1455V301H1511Z" },                  // Lá#
        { tipo: 'branca', d: "M1597 521.67H1483V301.003H1511V1.00299H1597V521.67Z" }  // Si
    ];

    return (
        <svg xmlns="http://www.w3.org/2000/svg" width="1598" height="523" viewBox="0 0 1598 523" fill="none">
            {teclas.map((tecla, index) => {
                const numeroNota = 26 + index; 
                
                const isAtiva = notasAtivas.includes(numeroNota);

                let fillColor;
                if (isAtiva) {
                    fillColor = "orange";
                } else {
                    if (tecla.tipo === 'branca') fillColor = "white";
                    else fillColor = "black";
                }

                return (
                    <path 
                        key={index}
                        d={tecla.d} 
                        fill={fillColor} 
                        stroke="black" 
                        strokeWidth="2"
                    />
                );
            })}
        </svg>
    );

}
