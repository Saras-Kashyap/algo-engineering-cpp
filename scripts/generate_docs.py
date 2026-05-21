import json
import re

def build_markdown_table(data):
    # Setup the table headers
    md = "| ID | Problem Title | Difficulty | Category | Frequently Asked By |\n"
    md += "| :--- | :--- | :---: | :--- | :--- |\n"
    
    # Loop through the database and build the rows
    for prob in data['problems']:
        # Format the ID to have leading zeros (e.g., 0014)
        prob_id = f"{prob['id']:04d}"
        
        # Determine the emoji based on difficulty
        emoji = "🟢" if prob['difficulty'].lower() == "easy" else "🟡" if prob['difficulty'].lower() == "medium" else "🔴"
        
        # Format the file link (assumes your files are named like '0014_longest_common_prefix.hpp')
        file_name = f"{prob_id}_{prob['title'].lower().replace(' ', '_')}.hpp"
        link = f"./src/{prob['category']}/{file_name}"
        
        # Format the companies array into a comma-separated string of inline code blocks
        companies = ", ".join([f"`{c}`" for c in prob['companies']])
        
        # Construct the final row
        row = f"| **{prob_id}** | [{prob['title']}]({link}) | {emoji} {prob['difficulty']} | {prob['category'].capitalize()} | {companies} |\n"
        md += row
        
    return md

def main():
    # 1. Load the database
    with open('metadata/database.json', 'r', encoding='utf-8') as f:
        data = json.load(f)
        
    # 2. Generate the new table
    new_table = build_markdown_table(data)
    
    # 3. Read the current README
    with open('README.md', 'r', encoding='utf-8') as f:
        readme_content = f.read()
        
    # 4. Swap out the old table for the new one using regex
    pattern = r'(\n).*?(\n)'
    replacement = rf'\1{new_table}\2'
    updated_readme = re.sub(pattern, replacement, readme_content, flags=re.DOTALL)
    
    # 5. Save the updated README
    with open('README.md', 'w', encoding='utf-8') as f:
        f.write(updated_readme)
        
    print("✅ README.md successfully updated from database.json!")

if __name__ == "__main__":
    main()