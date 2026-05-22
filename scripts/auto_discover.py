import os
import re
import json
import glob
import csv

def load_company_mappings(csv_path):
    """Reads the CSV and creates a dictionary mapping Problem ID -> List of Companies."""
    company_map = {}
    try:
        with open(csv_path, mode='r', encoding='utf-8') as file:
            # DictReader automatically uses the first row as column headers
            reader = csv.DictReader(file)
            for row in reader:
                try:
                    prob_id = int(row['ID'])
                    # Split "Amazon, Meta" into a clean list: ["Amazon", "Meta"]
                    companies_str = row.get('Companies', '')
                    companies = [c.strip() for c in companies_str.split(',') if c.strip()]
                    company_map[prob_id] = companies
                except (ValueError, KeyError):
                    # Skip rows where ID is missing or not a number
                    continue
        print(f"📊 Loaded company data for {len(company_map)} problems from CSV.")
    except FileNotFoundError:
        print(f"⚠️ Warning: CSV not found at {csv_path}. Proceeding without company data.")
    
    return company_map

def discover_problems():
    print("🔍 Scanning C++ files for metadata...")
    
    # 1. Load the master CSV data into memory first
    csv_file_path = os.path.join('hubs', 'topics', 'Ultimate_Master.csv')
    company_database = load_company_mappings(csv_file_path)
    
    master_db = {"problems": []}
    source_files = glob.glob('src/**/*.hpp', recursive=True)
    
    for file_path in source_files:
        category = os.path.basename(os.path.dirname(file_path))
        
        with open(file_path, 'r', encoding='utf-8') as f:
            content = f.read()
            
            id_match = re.search(r'\*\s*ID:\s*(\d+)', content)
            title_match = re.search(r'\*\s*Title:\s*(.+)', content)
            diff_match = re.search(r'\*\s*Difficulty:\s*(.+)', content)
            
            if id_match and title_match:
                prob_id = int(id_match.group(1))
                
                # 2. Query the dictionary for this ID to get the companies
                # If the ID isn't in the CSV, it defaults to an empty list []
                companies = company_database.get(prob_id, [])
                
                master_db["problems"].append({
                    "id": prob_id,
                    "title": title_match.group(1).strip(),
                    "difficulty": diff_match.group(1).strip() if diff_match else "Unknown",
                    "category": category,
                    "companies": companies  # Injected directly from the CSV!
                })

    master_db["problems"].sort(key=lambda x: x["id"])

    os.makedirs('metadata', exist_ok=True)
    with open('metadata/database.json', 'w', encoding='utf-8') as f:
        json.dump(master_db, f, indent=4)
        
    print(f"✅ Auto-discovery complete! Saved {len(master_db['problems'])} unique problems to database.json.")

if __name__ == "__main__":
    discover_problems()