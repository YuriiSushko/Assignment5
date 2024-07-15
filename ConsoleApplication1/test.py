import subprocess


def run_echo(input_data):
    try:
        process = subprocess.Popen(
            ['D:/Programming paradigms/Assignment5/ConsoleApplication1/x64/Debug/Intepreter.exe'],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        stdout, stderr = process.communicate(input_data)
        return stdout.strip(), stderr.strip()

    except Exception as e:
        print(f"Error running subprocess: {e}")
        return "", str(e)


def test_echo():
    tests = [
        {
            "input": "Hello, world!\n",
            "expected_output": "Echo: Hello, world!"
        },
        {
            "input": "12345\n",
            "expected_output": "Echo: 12345"
        },
        {
            "input": "Testing echo program\n",
            "expected_output": "Echo: Testing echo program"
        }
        # Add more test cases as needed
    ]
    for test in tests:
        input_data = test["input"]
        expected_output = test["expected_output"]

        output, error = run_echo(input_data)

        if error:
            print(f"Test failed for input:\n{input_data}")
            print(f"Error:\n{error}")
        elif output.strip() != expected_output:
            print(f"Test failed for input:\n{input_data}")
            print(f"Expected:\n{expected_output}")
            print(f"Got:\n{output}")
        else:
            print(f"Test passed for input:\n{input_data}")


if __name__ == "__main__":
    test_echo()
