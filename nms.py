from typing import Union
import numpy as np


def iou(box1: Union[list, np.ndarray], box2: Union[list, np.ndarray]) -> float:
    """
    box format is [x1, y1, x2, y2]
    """
    x_min = max(box1[0], box2[0])
    y_min = max(box1[1], box2[1])
    x_max = min(box1[2], box2[2])
    y_max = min(box1[3], box2[3])

    if x_min >= x_max or y_min >= y_max:
        return 0.0

    inter = (x_max - x_min) * (y_max - y_min)
    area1 = (box1[2] - box1[0]) * (box1[3] - box1[1])
    area2 = (box2[2] - box2[0]) * (box2[3] - box2[1])
    return inter / (area1 + area2 - inter)


def nms(
    bboxes: np.ndarray, scores: np.ndarray, iou_thr=0.7, conf_thr=None
) -> np.ndarray:
    """
    Args:
        bboxes(np.ndarray): bounding boxes with shape [N, 4], format is [x1, y1, x2, y2]
        scores(np.ndarray): object scores with shape [N]
    Rets:
        keep_ids(np.ndarray): bbox indexes with shape [n]
    """
    if conf_thr is not None:
        pos = scores > conf_thr
        bboxes, scores = bboxes[pos], scores[pos]

    sort_idx = np.argsort(scores)[::-1]
    keep_ids = []
    while len(sort_idx) > 0:
        idx = sort_idx[0]
        keep_ids.append(idx)

        sort_idx = sort_idx[1:]  # pop selected idx
        ious = np.array([iou(bboxes[idx], bboxes[i]) for i in sort_idx])
        remove_indices = np.where(ious > iou_thr)[0]
        sort_idx = np.delete(sort_idx, remove_indices)

    return np.array(keep_ids)
