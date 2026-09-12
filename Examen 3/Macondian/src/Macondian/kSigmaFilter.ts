export interface VectorStats {
  rawVector: number[];
  mean: number;
}

export const processSingleVector = (vector: number[]): VectorStats => {
  if (!vector || vector.length === 0) {
    return { rawVector: [], mean: 0 };
  }
  const mean = vector.reduce((acc, val) => acc + val, 0) / vector.length;
  return { rawVector: vector, mean };
};