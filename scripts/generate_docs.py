import json
import os

def main():
    print("📝 Generating a professional README table...")
    
    # Robust Path Resolving
    script_dir = os.path.dirname(os.path.abspath(__file__))
    root_dir = os.path.join(script_dir, "..")
    
    db_path = os.path.join(root_dir, 'metadata', 'database.json')
    readme_path = os.path.join(root_dir, 'src', 'README.md')
    
    try:
        with open(db_path, 'r', encoding='utf-8') as f:
            data = json.load(f)
    except FileNotFoundError:
        print(f"❌ Error: {db_path} not found. Have you run auto_discover.py yet?")
        return

    # UPDATED: Added the 'Companies' column to the table header
    table_content = "\n| # | Problem Title | Difficulty | Category | Companies | LeetCode | Solution |\n"
    table_content += "| :---: | :--- | :---: | :--- | :--- | :---: | :---: |\n"
    
    for prob in data.get('problems', []):
        prob_id = f"{prob['id']:04d}"
        title = prob['title']
        category = prob.get('category', 'Unknown')
        companies_list = prob.get('companies', [])
        
        diff = prob.get('difficulty', 'Unknown').lower()
        if diff == "easy":
            diff_html = "🟩 Easy"
        elif diff == "medium":
            diff_html = "🟨 Medium"
        elif diff == "hard":
            diff_html = "🟥 Hard"
        else:
            diff_html = "⬜ Unknown"
            
        safe_title = title.lower().replace(' ', '_').replace('-', '_').replace("'", "")
        file_name = f"{prob_id}_{safe_title}.hpp"
        
        safe_category = category.lower()
        local_link = f"./{safe_category}/{file_name}"
        
        lc_slug = title.lower().replace(' ', '-').replace("'", "")
        lc_link = f"https://leetcode.com/problems/{lc_slug}/"
        
        # UPDATED: Format the companies array into a bolded, comma-separated string
        if companies_list:
            companies_str = ", ".join([f"**{c}**" for c in companies_list])
        else:
            companies_str = "-"
            
        # Inject the companies_str into the Markdown row
        table_content += f"| **{prob_id}** | {title} | {diff_html} | `{category.capitalize()}` | {companies_str} | [🔗 Link]({lc_link}) | [💻 Code]({local_link}) |\n"

    try:
        with open(readme_path, 'r', encoding='utf-8') as f:
            lines = f.readlines()
    except FileNotFoundError:
        print(f"❌ Error: {readme_path} not found.")
        return
        
    start_marker = "[TABLE_START]"
    end_marker = "[TABLE_END]"
    
    start_idx = -1
    end_idx = -1
    
    for i, line in enumerate(lines):
        if start_marker in line:
            start_idx = i
        elif end_marker in line:
            end_idx = i
            
    if start_idx == -1 or end_idx == -1 or start_idx >= end_idx:
        print(f"❌ Error: Markers missing or incorrectly placed in {readme_path}.")
        print("Please ensure exactly [TABLE_START] and [TABLE_END] are in the file on separate lines.")
        return
        
    top_half = lines[:start_idx + 1]
    bottom_half = lines[end_idx:]
    
    new_readme_lines = top_half + [table_content + "\n"] + bottom_half
    
    with open(readme_path, 'w', encoding='utf-8') as f:
        f.writelines(new_readme_lines)
        
    print(f"✅ SUCCESS! Professional table generated in {readme_path}.")

if __name__ == "__main__":
    main()