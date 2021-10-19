import fiftyone as fo
import fiftyone.zoo as foz
if __name__ == '__main__':
    dataset = foz.load_zoo_dataset(
    "coco-2017",
    split="validation",
    label_types=["segmentations"],
    classes=["sports ball"],
    max_samples=25,
)   

session = fo.launch_app(dataset)
