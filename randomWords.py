import random
import os

# Sample sentences to ensure a variety of words and contexts.
base_sentences = [
    "The quick brown fox jumps over the lazy dog.",
    "After years of hard work, she finally achieved her dream of becoming a doctor.",
    "Despite the heavy rain, the event went on as planned.",
    "He said, 'With great power comes great responsibility.'",
    "As the sun set, the sky turned a beautiful shade of orange.",
    "Can you believe she's never been to the ocean before?",
    "The museum's new exhibit on ancient Egypt is fascinating.",
    "I'm reading a book on the history of science, and it's quite intriguing.",
    "She whispered, 'I think someone's following us.'",
    "According to the latest research, a healthy diet can significantly improve your mood.",
]

# Function to generate random sentences - simplistic for demonstration.
def generate_random_sentence():
    subjects = ["He", "She", "The cat", "The robot", "Our neighbor"]
    verbs = ["ate", "jumped over", "ran towards", "found", "lost"]
    objects = ["a sandwich.", "the fence.", "a shiny object.", "the keys.", "a secret."]
    return random.choice(subjects) + " " + random.choice(verbs) + " " + random.choice(objects)

# Generate and add random sentences to base_sentences to reach the desired total.
total_sentences_needed = 1000
while len(base_sentences) < total_sentences_needed:
    base_sentences.append(generate_random_sentence())

# Writing sentences to a .txt file.
file_path = "/mnt/data/test_sentences.txt"
with open(file_path, "w") as file:
    for sentence in base_sentences:
        file.write(sentence + "\n")

file_path
