import React, { useState } from "react";
import { processBatches, BatchAnalysisResult } from "./Macondian/batchProcessor";
import Monitor from "./Monitor";
import { processRawSignalText } from "./Macondian/MacondianParser";

export const Test = (props: any) => {
  const rawLog: string[] = props.rawLog || [];

  // Datos de prueba estáticos simulando etiquetas de canales
  const [data] = useState([
    { tag: "L1001", rawVector: [10.2, 11.5, 9.8, 10.1], mean: 10.4 },
    { tag: "L1001", rawVector: [85.0, 88.2, 90.1, 84.5], mean: 86.95 }, // Outlier para L1001
    { tag: "Y1001", rawVector: [1.8, 1.9, 1.85, 1.95], mean: 1.875 },
    { tag: "Y1001", rawVector: [1.82, 1.88, 1.9, 1.86], mean: 1.865 },
  ]);

  const [result, setResult] = useState<BatchAnalysisResult | null>(null);

  const handleProcess = () => {
    const analysis = processBatches(data, 2);
    setResult(analysis);
  };

  return (
    <div style={{ padding: "20px", color: "#fff", fontFamily: "sans-serif" }}>
      {/* MONITORES EN TIEMPO REAL */}
      <div style={{ marginBottom: "30px" }}>
        <h3>Monitores de Señal en Tiempo Real</h3>
        <div style={{ display: "flex", width: "100%", height: "250px", gap: "10px" }}>
          <div style={{ flex: 1, height: "100%" }}>
            <Monitor title="Señal cruda" log={rawLog} />
          </div>
          <div style={{ flex: 1, height: "100%" }}>
            <Monitor 
              title="Serie Filtrada (Promedios por Canal)" 
              log={processRawSignalText(rawLog.join("\n"), 2).split("\n")} 
            />
          </div>
        </div>
      </div>

      <hr style={{ borderColor: "#444", marginBottom: "30px" }} />

      {/* PRUEBA DE LOTES ESTÁTICA */}
      <div style={{ display: "flex", justifyContent: "space-between", alignItems: "center", marginBottom: "20px" }}>
        <h2>Pantalla Test: Procesamiento 2-Sigma por Canal</h2>
        <button
          onClick={handleProcess}
          style={{
            backgroundColor: "#2e7d32",
            color: "#fff",
            border: "none",
            padding: "8px 16px",
            borderRadius: "4px",
            cursor: "pointer",
            fontWeight: "bold",
          }}
        >
          Procesar Batches
        </button>
      </div>

      {result && (
        <div>
          {/* Malla de estadísticas por Canal / Etiqueta */}
          <h3>Métricas Globales por Canal (μ, σ y Trimmed)</h3>
          <div style={{ display: "flex", gap: "12px", marginBottom: "20px", flexWrap: "wrap" }}>
            {Object.keys(result.tagStats).map((tag) => (
              <div key={tag} style={boxStyle}>
                <small style={{ color: "#aaa" }}>Canal {tag}</small>
                <div style={numStyle}>μ Global: {result.tagStats[tag].globalMean.toFixed(3)}</div>
                <div style={{ fontSize: "14px", color: "#81c784" }}>
                  σ StdDev: {result.tagStats[tag].stdDev.toFixed(3)}
                </div>
                <div style={{ fontSize: "14px", color: "#64b5f6", marginTop: "4px" }}>
                  μ Cortado: {result.tagStats[tag].trimmedMean.toFixed(3)}
                </div>
              </div>
            ))}
          </div>

          <h3>Estado de Vectores de Entrada</h3>
          {result.vectorSummaries.map((item, idx) => {
            const isClean = result.cleanIndices.has(idx);
            return (
              <div 
                key={idx} 
                style={{
                  ...batchRowStyle,
                  borderColor: isClean ? "#2e7d32" : "#c62828",
                  backgroundColor: isClean ? "#1b2e1e" : "#2e1b1b"
                }}
              >
                <div style={{ display: "flex", justifyContent: "space-between" }}>
                  <strong>{item.tag}</strong>
                  <span style={{ color: isClean ? "#81c784" : "#e57373", fontWeight: "bold" }}>
                    {isClean ? "VÁLIDO (Dentro de 2σ)" : "DESCARTADO (Outlier)"}
                  </span>
                </div>

                <div style={{ marginTop: "6px" }}>
                  <small style={{ color: "#aaa" }}>Promedio del lote: </small>
                  <span style={tagStyle}>{item.mean.toFixed(3)}</span>
                </div>

                <div style={{ marginTop: "6px" }}>
                  <small style={{ color: "#aaa" }}>Valores: </small>
                  {item.rawVector.map((val: number, i: number) => (
                    <span key={i} style={tagStyle}>
                      {val}
                    </span>
                  ))}
                </div>
              </div>
            );
          })}
        </div>
      )}
    </div>
  );
};

const boxStyle: React.CSSProperties = {
  backgroundColor: "#1e1e1e",
  padding: "12px",
  borderRadius: "6px",
  flex: 1,
  minWidth: "180px",
  border: "1px solid #333",
};

const numStyle: React.CSSProperties = {
  fontSize: "16px",
  fontWeight: "bold",
  marginTop: "4px",
};

const batchRowStyle: React.CSSProperties = {
  padding: "12px",
  borderRadius: "6px",
  marginBottom: "10px",
  border: "1px solid",
};

const tagStyle: React.CSSProperties = {
  display: "inline-block",
  padding: "2px 6px",
  borderRadius: "3px",
  fontSize: "12px",
  marginRight: "4px",
  backgroundColor: "#424242",
};

export default Test;