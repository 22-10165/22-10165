import { processBatches, VectorEntry } from "./batchProcessor";

export function processRawSignalText(rawText: string, k: number = 2): string {
  if (!rawText || typeof rawText !== "string") return "";

  // 0. Si la entrada ya traía un resumen previo, nos quedamos solo con la parte de la señal cruda
  const cleanRawText = rawText.split("--- RESUMEN GLOBAL POR ETIQUETA ---")[0].trim();

  const lines = cleanRawText.split("\n");
  const extractedEntries: VectorEntry[] = [];
  const lineToEntryIndex: { [lineIdx: number]: number } = {};

  // 1. Extraer etiqueta y vector numérico de cada línea
  lines.forEach((line, lineIdx) => {
    const match = line.match(/^(.*?)\s*\[(.*?)\]/);
    if (match) {
      const tagLabel = match[1].trim(); // Ej: "16 L1001"
      const numbers = match[2]
        .split(",")
        .map((val) => parseFloat(val.trim()))
        .filter((val) => !isNaN(val));

      if (numbers.length > 0) {
        const mean = numbers.reduce((a, b) => a + b, 0) / numbers.length;
        lineToEntryIndex[lineIdx] = extractedEntries.length;
        extractedEntries.push({
          tag: tagLabel,
          rawVector: numbers,
          mean
        });
      }
    }
  });

  if (extractedEntries.length === 0) return cleanRawText;

  // 2. Procesar estadísticas agrupando por etiqueta sobre todos los batches
  const result = processBatches(extractedEntries, k);

  const processedLines: string[] = [];

  // 3. Formatear cada línea con el promedio del batch individual
  lines.forEach((line, lineIdx) => {
    const entryIdx = lineToEntryIndex[lineIdx];

    if (entryIdx === undefined) {
      processedLines.push(line);
      return;
    }

    const entry = extractedEntries[entryIdx];
    processedLines.push(line.replace(/\[.*?\]/, `[ ${entry.mean.toFixed(3)} ]`));
  });

  // 4. UN SOLO RESUMEN GLOBAL AL FINAL
  processedLines.push("\n--- RESUMEN GLOBAL POR ETIQUETA ---");
  
  Object.keys(result.tagStats).forEach((tag) => {
    const stats = result.tagStats[tag];
    processedLines.push(
      `${tag} -> Promedio Global: ${stats.globalMean.toFixed(3)} | Desviación Std: ${stats.stdDev.toFixed(3)} | Promedio Cortado (Trimmed): ${stats.trimmedMean.toFixed(3)}`
    );
  });

  return processedLines.join("\n");
}