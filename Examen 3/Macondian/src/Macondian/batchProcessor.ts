export interface VectorEntry {
  tag: string;
  rawVector: number[];
  mean: number;
}

export interface TagMetrics {
  globalMean: number;
  stdDev: number;
  trimmedMean: number;
  totalBatches: number;
  cleanBatches: number;
}

export interface BatchAnalysisResult {
  tagStats: { [tag: string]: TagMetrics };
  cleanIndices: Set<number>;
  vectorSummaries: VectorEntry[];
}

export function processBatches(
  input: VectorEntry[],
  k: number = 2
): BatchAnalysisResult {
  if (!input || input.length === 0) {
    return { tagStats: {}, cleanIndices: new Set(), vectorSummaries: [] };
  }

  // 1. Agrupar los promedios de cada batch por su canal/etiqueta (ej. "L1001", "Y1003")
  const meansByTag: { [tag: string]: number[] } = {};

  input.forEach((item) => {
    const cleanTag = item.tag.replace(/^\d+\s+/, "").trim(); // Limpia el número de batch "16 L1001" -> "L1001"
    if (!meansByTag[cleanTag]) {
      meansByTag[cleanTag] = [];
    }
    meansByTag[cleanTag].push(item.mean);
  });

  // 2. Calcular Media Global, Desviación Estándar y Promedio Cortado por Etiqueta
  const tagStats: { [tag: string]: TagMetrics } = {};

  Object.keys(meansByTag).forEach((tag) => {
    const means = meansByTag[tag];
    const totalBatches = means.length;

    // Promedio Global (μ)
    const globalMean = means.reduce((a, b) => a + b, 0) / totalBatches;

    // Desviación Estándar Global (σ)
    const variance = means.reduce((acc, m) => acc + Math.pow(m - globalMean, 2), 0) / totalBatches;
    const stdDev = Math.sqrt(variance);

    // Filtro k-Sigma
    const lowerBound = globalMean - k * stdDev;
    const upperBound = globalMean + k * stdDev;

    // Filtrar lotes válidos
    const validMeans = means.filter((m) => m >= lowerBound && m <= upperBound);

    // Promedio Cortado (Trimmed Mean)
    const trimmedMean = validMeans.length > 0
      ? validMeans.reduce((a, b) => a + b, 0) / validMeans.length
      : globalMean;

    tagStats[tag] = {
      globalMean,
      stdDev,
      trimmedMean,
      totalBatches,
      cleanBatches: validMeans.length
    };
  });

  // 3. Determinar qué índices individuales superan el filtro
  const cleanIndices = new Set<number>();

  input.forEach((item, idx) => {
    const cleanTag = item.tag.replace(/^\d+\s+/, "").trim();
    const stats = tagStats[cleanTag];

    if (stats) {
      const lower = stats.globalMean - k * stats.stdDev;
      const upper = stats.globalMean + k * stats.stdDev;

      if (item.mean >= lower && item.mean <= upper) {
        cleanIndices.add(idx);
      }
    } else {
      cleanIndices.add(idx);
    }
  });

  return {
    tagStats,
    cleanIndices,
    vectorSummaries: input
  };
}