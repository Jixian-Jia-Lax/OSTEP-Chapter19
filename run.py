import subprocess
import numpy as np
import matplotlib.pyplot as plt  

def experiment(num_of_pages, num_of_trials):
    # Run the C program with the parameters
    result = subprocess.run(["./tlb", str(num_of_pages), str(num_of_trials)], capture_output=True, text=True)

    # Convert the captured output to a long int
    print("DEBUG: result.stdout:", result.stdout)
    result = float(result.stdout.strip())

    return (result*pow(10,3))/num_of_trials

def main():
    num_of_trials = 5000
    num_of_pages = 2
    iterations = 10

    num_of_pages_values = []
    c_program_results = []

    for _ in range(iterations):
        result = experiment(num_of_pages, num_of_trials)
        
        num_of_pages_values.append(num_of_pages)
        c_program_results.append(result)

        num_of_pages *= 2  # double the value of param1 in each iteration

    # Plotting using matplotlib
    plt.plot(num_of_pages_values, c_program_results, 'o-', label='Results from C program')
    plt.xlabel('Number of Pages')
    plt.ylabel('Time Per Access (ns)')
    plt.title('Param1 vs Results from C program')
    plt.legend()
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    main()
