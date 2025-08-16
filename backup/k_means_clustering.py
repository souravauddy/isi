from __future__ import annotations
import sys
import pandas as pd
import numpy as np
import scipy.spatial
import sklearn
import matplotlib.pyplot as plt
from typing import (
    Self,
    Final,
)

import sklearn
import sklearn.cluster


INF: Final[int] = sys.maxsize


class KMeans(object):
    def __init__(self, n_clusters: int = 3) -> None:
        self.n_clusters = n_clusters

    def _cluster_centroid(self, cluster: np.ndarray, dimension: int) -> np.ndarray[np.float64]:
        cluster_length = len(cluster)
        centroid = np.zeros(dimension)

        for co_ordinate in cluster:
            centroid += np.array(co_ordinate)

        centroid = centroid / cluster_length
        return list(centroid)
        # print(centroid / cluster_length)

    def fit(self, Data: pd.DataFrame) -> Self:
        list_co_ordinates = []

        for index in Data.index:
            row_vector = []

            for feature in Data.columns:
                row_vector.append(Data.loc[index, feature])

            list_co_ordinates.append(row_vector)

        co_ordinates = np.array(list_co_ordinates)
        random_points_index = np.random.choice(
            co_ordinates.shape[0], self.n_clusters, replace=False)
        random_points = [co_ordinates[index] for index in random_points_index]
        print(random_points)

        def compute_clusters(input_centroid: np.ndarray[np.float64]) -> np.ndarray[list[int]]:
            clusters = [[] for _ in range(self.n_clusters)]

            for co_ordinate in co_ordinates:
                minimum_distance = INF
                minimum_index = -1

                for centroid_index, centroid in enumerate(input_centroid):
                    distance = scipy.spatial.distance.euclidean(co_ordinate, centroid)

                    if distance < minimum_distance:
                        minimum_index = centroid_index
                        minimum_distance = distance

                assert minimum_index != -1, "This should not happen"
                clusters[minimum_index].append(co_ordinate)

            return clusters

        clusters = compute_clusters(random_points)
        # print("clusters", clusters)

        while True:
            current_centroids = [self._cluster_centroid(cluster, len(Data.columns)) for cluster in clusters]
            new_clusters = compute_clusters(current_centroids)
            computed_centroids = [self._cluster_centroid(cluster, len(Data.columns)) for cluster in new_clusters]
            print(current_centroids, computed_centroids, sep='\n')

            if current_centroids == computed_centroids:
                break

            current_centroids = computed_centroids
            clusters = new_clusters

        print(clusters)


def main() -> int:
    data = pd.DataFrame({
        "Height": [185, 170, 168, 179, 182, 188, 180, 180, 183, 180, 180, 177],
        "Weight": [72, 56, 60, 68, 72, 77, 71, 70, 84, 88, 67, 76]
    })

    KMeans_clusters = KMeans(n_clusters=2)
    another_cluster = sklearn.cluster.KMeans(n_clusters=2)
    another_cluster.fit(data)
    KMeans_clusters.fit(data)
    print(another_cluster.cluster_centers_)

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
