import sys
import pandas as pd
import matplotlib.pyplot as plt
from pathlib import Path


def main():
    if len(sys.argv) < 3:
        print("Usage: python plot_results.py <results.csv> <output_dir>")
        return 1

    csv_path = Path(sys.argv[1])
    output_dir = Path(sys.argv[2])

    if not csv_path.exists():
        print(f"CSV file not found: {csv_path}")
        return 1

    df = pd.read_csv(csv_path)

    algorithms = df["Algorithm"]

    def plot(metric, title, filename):
        plt.figure()
        plt.bar(algorithms, df[metric])
        plt.title(title)
        plt.ylabel(metric)
        plt.grid(axis='y')
        plt.tight_layout()
        plt.savefig(output_dir / filename, dpi=150)
        plt.close()

    plot("AvgWaitingTime", "Average Waiting Time", "avg_waiting_time.png")
    plot("AvgTurnaroundTime", "Average Turnaround Time", "avg_turnaround_time.png")
    plot("ContextSwitches", "Context Switches", "context_switches.png")

    print("Plots generated:")
    print(" - avg_waiting_time.png")
    print(" - avg_turnaround_time.png")
    print(" - context_switches.png")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
