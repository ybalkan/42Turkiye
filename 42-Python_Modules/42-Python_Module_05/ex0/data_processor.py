import abc
import typing
from typing import Any

class DataProcessor(abc.ABC):
    def __init__(self) -> None:
        self._data: list[tuple[int, str]] = []
        self._total_processed: int = 0

    @abc.abstractmethod
    def validate(self, data: Any) -> bool:
        pass

    @abc.abstractmethod
    def ingest(self, data: Any) -> None:
        pass

    def output(self) -> tuple[int, str]:
        if not self._data:
            raise IndexError("No data to output")
        return self._data.pop(0)

class NumericProcessor(DataProcessor):
    def validate(self, data: Any) -> bool:
        if isinstance(data, (int, float)):
            return not isinstance(data, bool)
        if isinstance(data, list):
            return all(isinstance(x, (int, float)) and not isinstance(x, bool) for x in data)
        return False

    def ingest(self, data: int | float | list[int | float]) -> None:
        if not self.validate(data):
            raise ValueError("Improper numeric data")
        if isinstance(data, list):
            for item in data:
                self._data.append((self._total_processed, str(item)))
                self._total_processed += 1
        else:
            self._data.append((self._total_processed, str(data)))
            self._total_processed += 1

class TextProcessor(DataProcessor):
    def validate(self, data: Any) -> bool:
        if isinstance(data, str):
            return True
        if isinstance(data, list):
            return all(isinstance(x, str) for x in data)
        return False

    def ingest(self, data: str | list[str]) -> None:
        if not self.validate(data):
            raise ValueError("Improper text data")
        if isinstance(data, list):
            for item in data:
                self._data.append((self._total_processed, item))
                self._total_processed += 1
        else:
            self._data.append((self._total_processed, data))
            self._total_processed += 1

class LogProcessor(DataProcessor):
    def validate(self, data: Any) -> bool:
        def is_valid_dict(d: Any) -> bool:
            return isinstance(d, dict) and all(isinstance(k, str) and isinstance(v, str) for k, v in d.items())
        
        if is_valid_dict(data):
            return True
        if isinstance(data, list):
            return all(is_valid_dict(x) for x in data)
        return False

    def ingest(self, data: dict[str, str] | list[dict[str, str]]) -> None:
        if not self.validate(data):
            raise ValueError("Improper log data")
        if isinstance(data, dict):
            items = [data]
        else:
            items = data
            
        for item in items:
            s = ": ".join(item.values())
            self._data.append((self._total_processed, s))
            self._total_processed += 1

if __name__ == "__main__":
    print("=== Code Nexus - Data Processor ===")
    
    print("\nTesting Numeric Processor...")
    np = NumericProcessor()
    print(f"Trying to validate input '42': {np.validate(42)}")
    print(f"Trying to validate input 'Hello': {np.validate('Hello')}")
    print("Test invalid ingestion of string 'foo' without prior validation:")
    try:
        np.ingest("foo") # type: ignore
    except Exception as e:
        print(f"Got exception: {e}")
        
    np_data: list[int | float] = [1, 2, 3, 4, 5]
    print(f"Processing data: {np_data}")
    np.ingest(np_data)
    print("Extracting 3 values...")
    for i in range(3):
        rank, val = np.output()
        print(f"Numeric value {rank}: {val}")
        
    print("\nTesting Text Processor...")
    tp = TextProcessor()
    print(f"Trying to validate input '42': {tp.validate(42)}")
    tp_data: list[str] = ['Hello', 'Nexus', 'World']
    print(f"Processing data: {tp_data}")
    tp.ingest(tp_data)
    print("Extracting 1 value...")
    rank, val = tp.output()
    print(f"Text value {rank}: {val}")
    
    print("\nTesting Log Processor...")
    lp = LogProcessor()
    print(f"Trying to validate input 'Hello': {lp.validate('Hello')}")
    lp_data: list[dict[str, str]] = [{'log_level': 'NOTICE', 'log_message': 'Connection to server'}, {'log_level': 'ERROR', 'log_message': 'Unauthorized access!!'}]
    print(f"Processing data: {lp_data}")
    lp.ingest(lp_data)
    print("Extracting 2 values...")
    for i in range(2):
        rank, val = lp.output()
        print(f"Log entry {rank}: {val}")
